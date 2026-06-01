
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <type_traits>
 
using namespace std;
 
 
template <typename L, typename R>
struct VecAdd {
    L lhs;
    R rhs;
    template<typename LL, typename RR>
    VecAdd(LL&& l, RR&& r) : lhs(std::forward<LL>(l)), rhs(std::forward<RR>(r)) {}
    int operator[](int i) const { return lhs[i] + rhs[i]; }
};
 
template <typename L, typename R>
struct VecSub {
    L lhs;
    R rhs;
    template<typename LL, typename RR>
    VecSub(LL&& l, RR&& r) : lhs(std::forward<LL>(l)), rhs(std::forward<RR>(r)) {}
    int operator[](int i) const { return lhs[i] - rhs[i]; }
};
 
template <typename R>
struct VecScalarMul {
    int scalar;
    R rhs;
    template<typename RR>
    VecScalarMul(int s, RR&& r) : scalar(s), rhs(std::forward<RR>(r)) {}
    int operator[](int i) const { return scalar * rhs[i]; }
};
 
 
template <int N>
class Vector {
    int data[N];
 
    template<typename Expr>
    using IsNotVector = std::enable_if_t<
        !std::is_same<typename std::decay<Expr>::type, Vector>::value>;
 
public:
    Vector() {
        for (int i = 0; i < N; ++i) data[i] = 0;
        cout << " Default constr\n";
    }
 
    Vector(std::initializer_list<int> list) {
        cout << " Init list constr\n";
        auto it = list.begin();
        for (int i = 0; i < N; ++i)
            data[i] = (it != list.end()) ? *it++ : 0;
    }
 
    Vector(const Vector& other) {
        std::copy(other.data, other.data + N, data);
        cout << " Copy constr\n";
    }
 
    Vector(Vector&& other) noexcept {
        std::copy(other.data, other.data + N, data);
        cout << " Move constr\n";
    }
 
    template <typename Expr, typename = IsNotVector<Expr>>
    Vector(Expr&& expr) {
        cout << " Expr constr\n";
        for (int i = 0; i < N; ++i)
            data[i] = expr[i];
    }
 
    template <typename Expr, typename = IsNotVector<Expr>>
    Vector& operator=(Expr&& expr) {
        for (int i = 0; i < N; ++i)
            data[i] = expr[i];
        return *this;
    }
 
    int  operator[](int i) const { return data[i]; }
    int& operator[](int i)       { return data[i]; }
 
    friend ostream& operator<<(ostream& out, const Vector& v) {
        for (int i = 0; i < N; ++i)
            out << v.data[i] << (i == N-1 ? "" : ", ");
        return out;
    }
};
 
// ── Operatory — budują węzły drzewa (perfect forwarding) ─────────────────
 
template <typename L, typename R>
auto operator+(L&& lhs, R&& rhs)
    -> VecAdd<typename std::decay<L>::type, typename std::decay<R>::type>
{
    return VecAdd<typename std::decay<L>::type, typename std::decay<R>::type>(
        std::forward<L>(lhs), std::forward<R>(rhs));
}
 
template <typename L, typename R>
auto operator-(L&& lhs, R&& rhs)
    -> VecSub<typename std::decay<L>::type, typename std::decay<R>::type>
{
    return VecSub<typename std::decay<L>::type, typename std::decay<R>::type>(
        std::forward<L>(lhs), std::forward<R>(rhs));
}
 
template <typename R>
auto operator*(int s, R&& expr)
    -> VecScalarMul<typename std::decay<R>::type>
{
    return VecScalarMul<typename std::decay<R>::type>(s, std::forward<R>(expr));
}
 
int main(){
  using V = Vector<10>;
  V v{1,2,3,4,5,6,7,8,9,10};
  V x(v);
  V y{4,4,2,5,3,2,3,4,2,1};

  cout << "Lazy operations :\n";
  V z = v + x + 3 * y - 2 * x;
  cout << z << endl;
  
  int e = (z+x+y)[2];
  cout << " e = " << e << endl;
  V w = v + x + 3 * y - 2 * x;
  cout << w[2] << endl;
  return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */
