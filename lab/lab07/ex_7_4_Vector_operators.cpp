#include <iostream>
#include <initializer_list>
#include <algorithm>

using namespace std;

template <typename L, typename R>
struct VecAdd {
    const L& lhs;
    const R& rhs;
    VecAdd(const L& l, const R& r) : lhs(l), rhs(r) {}
    int operator[](int i) const { return lhs[i] + rhs[i]; }
};

template <typename L, typename R>
struct VecSub {
    const L& lhs;
    const R& rhs;
    VecSub(const L& l, const R& r) : lhs(l), rhs(r) {}
    int operator[](int i) const { return lhs[i] - rhs[i]; }
};

template <typename R>
struct VecScalarMul {
    int scalar;
    const R& rhs;
    VecScalarMul(int s, const R& r) : scalar(s), rhs(r) {}
    int operator[](int i) const { return scalar * rhs[i]; }
};

template <int N>
class Vector {
    int data[N];
public:
    Vector() {
        for (int i = 0; i < N; ++i) data[i] = 0;
        cout << " Default constr" << endl;
    }
    Vector(std::initializer_list<int> list) {
        cout << " Init list constr" << endl;
        auto it = list.begin();
        for (int i = 0; i < N && it != list.end(); i++) {
            data[i] = *it++;
        }
    }
    Vector(const Vector& m) {
        std::copy(m.data, m.data + N, data);
        cout << " Copy constr" << endl;
    }
    template <typename Expr>
    Vector(const Expr& expr) {
        cout << " Default constr" << endl;
        for (int i = 0; i < N; ++i) {
            data[i] = expr[i];
        }
    }
    int operator[](int index) const {
        return data[index];
    }
    int& operator[](int index) {
        return data[index];
    }
    friend ostream& operator<<(ostream& out, const Vector& m) {
        for (int i = 0; i < N; i++) {
            out << m.data[i] << (i == N - 1 ? "" : ", ");
        }
        return out;
    }
};

template <typename L, int N>
VecAdd<L, Vector<N>> operator+(const L& lhs, const Vector<N>& rhs) {
    return VecAdd<L, Vector<N>>(lhs, rhs);
}
template <typename L, typename R>
VecAdd<L, R> operator+(const L& lhs, const R& rhs) {
    return VecAdd<L, R>(lhs, rhs);
}
template <typename L, int N>
VecSub<L, Vector<N>> operator-(const L& lhs, const Vector<N>& rhs) {
    return VecSub<L, Vector<N>>(lhs, rhs);
}
template <typename L, typename R>
VecSub<L, R> operator-(const L& lhs, const R& rhs) {
    return VecSub<L, R>(lhs, rhs);
}
template <int N>
VecScalarMul<Vector<N>> operator*(int s, const Vector<N>& v) {
    return VecScalarMul<Vector<N>>(s, v);
}
template <typename R>
VecScalarMul<R> operator*(int s, const R& expr) {
    return VecScalarMul<R>(s, expr);
}

int main(){
  using V = Vector<10>;
  V v{1,2,3,4,5,6,7,8,9,10};
  V x(v);
  V y{4,4,2,5,3,2,3,4,2,1};

  cout << "Lazy operations :\n";
  // It does not create temporary Vectors
  // It computes resulting vector coordinate by coordinate
  // (evaluating whole expression)
  V z = v + x + 3 * y - 2 * x;
  cout << z << endl;
  
  // Computes only one coordinate of Vector
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
