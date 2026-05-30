#include <iostream>
#include <vector>
#include <concepts>
#include <iterator>
using namespace std;


template <typename T>
concept Container = requires(T a) {
    typename T::value_type;
    { a.begin() } -> std::input_or_output_iterator;
    { a.end() }   -> std::input_or_output_iterator;
    requires requires(typename T::value_type v) {
        { v + v } -> std::convertible_to<typename T::value_type>;
    };
};

template <typename T>
concept Printable = requires(T x) {
    { std::cout << x } -> std::same_as<std::ostream&>;
};

template <typename T>
concept HasPrintMethod = requires(const T x) {
    { x.print() };
};

void print(const auto& x) {
    using T = std::remove_cvref_t<decltype(x)>;

    if constexpr (Container<T>) {
        int i = 0;
        for (const auto& elem : x) {
            std::cout << i++ << " : ";
            print(elem);
            std::cout << "\n";
        }
        std::cout << "-------\n";
    } else if constexpr (Printable<T>) {
        std::cout << x << "\n-------\n";
    } else if constexpr (HasPrintMethod<T>) {
        x.print();
        std::cout << "\n-------\n";
    } else {
        static_assert(sizeof(T) == 0, "Type has neither operator<< nor print()");
    }
}

auto sum(const Container auto& c) {
    using V = typename std::remove_cvref_t<decltype(c)>::value_type;
    V total{};
    for (const auto& elem : c)
        total = total + elem;
    return total;
}

template <typename  T>
class A{
protected:
    T x;
public:
    A(T x = T()) : x(x) {}
    void print() const{
      cout << "[" << x << "]";
    }
    friend A operator+(const A & a, const A & b){
      return a.x + b.x;
    }

};

template <typename T>
class B: public A<T>{
public:
    using A<T>::A;
    B(const A<T> & a): A<T>(a) {}
    friend std::ostream & operator<<(std::ostream & out, const B & b){
      return (out << "#" << b.x << "#");
    }
};



using namespace std;
int main() {
  vector v{1,2,4,5};
  print(v);
  A<int> a{5};
  print(a);
  B<double> b{3.14};
  print(b);
  print(2.7);
  vector<A<int>> va{ 4, 5, 7, 9};
  vector<B<int>> vb{ 4, 5, 7, 9};
  print(va);
  print(vb);
  print( sum(v) );
  print( sum(vb) );
  return 0;
}
/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5
-------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]
-------
0 : #4#
1 : #5#
2 : #7#
3 : #9#
-------
12
#25#
*/