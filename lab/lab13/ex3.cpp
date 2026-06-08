#include <type_traits>
#include <iostream>
#include <iomanip>


template <int... Ns>
class IntegerList {
    static constexpr std::array<int, sizeof...(Ns)> arr = {Ns...};

public:
    static constexpr int size = sizeof...(Ns);

    static constexpr int get(int index) {
        return arr[index];
    }

    static constexpr int max() {
        int m = arr[0];
        for (int i = 1; i < size; ++i)
            if (arr[i] > m) m = arr[i];
        return m;
    }

    friend std::ostream& operator<<(std::ostream& os, IntegerList) {
        os << "[";
        int i = 0;
        ((os << (i++ ? ", " : "") << Ns), ...);
        return os << "]";
    }
};

template <int Index, typename List>
struct getInt;

template <int Index, int... Ns>
struct getInt<Index, IntegerList<Ns...>> {
    static constexpr int value = IntegerList<Ns...>::get(Index);
};

template <typename A, typename B>
struct Join;

template <int... As, int... Bs>
struct Join<IntegerList<As...>, IntegerList<Bs...>> {
    using type = IntegerList<As..., Bs...>;
};


template <typename List>
struct IsSorted;

template <int... Ns>
struct IsSorted<IntegerList<Ns...>> {
    static constexpr bool value = true;
};

template <int First, int Second, int... Rest>
struct IsSorted<IntegerList<First, Second, Rest...>> {
    static constexpr bool value =
        (First <= Second) && IsSorted<IntegerList<Second, Rest...>>::value;
};


template <typename List>
struct Max;

template <int... Ns>
struct Max<IntegerList<Ns...>> {
    static constexpr int value = IntegerList<Ns...>::max();
};


using namespace std;
    
int main() {

  using listA = 	IntegerList<5, -1, 5, 2, 1>;
  using listB =   IntegerList<1, 4, 6, 9>;
  cout << "List A : " << listA() << endl;
  cout << "List B : " << listB() << endl;

  cout << "A[1] = " << getInt<1, listA>::value << endl;
  cout << "B[3] = " << listB::get(3) << endl;
  static_assert( getInt<1, listA>::value == -1 );
  static_assert( listB::get(3) == 9 );
  static_assert( listB::get(1) == 4 );

  cout << boolalpha;
  cout << "Is A sorted? " << IsSorted<listA>::value << endl;
  cout << "Is B sorted? " << IsSorted<listB>::value << endl;

  using listC = Join<listA, listB>::type;

  cout << "List C : " << listC() << endl;
  cout << Max<listC>::value << endl;
  cout << listC::max() << endl;
  static_assert(listC::max() == 9 );
  static_assert(listA::max() == 5 );

}