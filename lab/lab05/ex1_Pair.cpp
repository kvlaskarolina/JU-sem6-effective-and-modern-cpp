#include <iostream>
//-------------------------------------------
/// ADD FORWARD DECLARATIONS HERE
template <typename T, typename S>
class Pair;

template <typename T, typename S>
std::ostream &operator<<(std::ostream &out, const Pair<T, S> &pair);
//-------------------------------------------
// DO NOT CHANGE CLASS Pair
template <typename T, typename S>
class Pair
{
    const T first;
    const S second;
    static int numberOfPair;

public:
    Pair(T first, S second) : first(first), second(second)
    {
        numberOfPair++;
    }
    template <typename P, typename R>
    explicit Pair(const Pair<P, R> &pair)
        : first(static_cast<T>(pair.getFirst())), second(static_cast<S>(pair.getSecond()))
    {
        numberOfPair++;
    } // Converting constructor, increases numberOfPairs - DONE
    ~Pair()
    {
        numberOfPair--;
    } // Destructor, decreases numberOfPair - DONE
    inline constexpr T getFirst() const
    {
        return first;
    } // returns first, mark it inline - DONE
    inline constexpr S getSecond() const
    {
        return second;
    } // returns second, mark it inline- DONE
    constexpr Pair<S, T> reverse() const
    {
        return Pair<S, T>(second, first);
    } // returns a reversed Pair - DONE
    constexpr static int getNumberOfPairs()
    {
        return numberOfPair;
    } // return the number of existing objects of Pair<T,S> - DONE
    // friend declaration with single template function operator<<(std::ostream, const Pair<T,S> &)
    friend std::ostream &operator<< <>(std::ostream &out, const Pair &pair);
    // friend declaration with class template (any Pair<P,R>)
    template <typename, typename>
    friend class Pair;
};
template <typename T, typename S>
int Pair<T, S>::numberOfPair = 0;

// Implement operator
template <typename T, typename S>
std::ostream &operator<<(std::ostream &out, const Pair<T, S> &pair)
{
    out << "(" << pair.first << ", " << pair.second << ")";
    return out;
}
//-------------------------------------------
/// IMPLEMENTATION SECTION: Implement methods here
//-------------------------------------------
using namespace std;
int main()
{

    Pair<int, double> p{1, 3.1415};
    cout << p.getFirst() << " " << p.getSecond() << endl;
    cout << p << endl;
    auto p2 = p.reverse();
    cout << p2 << endl;
    {
        Pair<int, int> p3(p);
        cout << p3 << endl;
        cout << Pair<int, int>::getNumberOfPairs() << endl;
    }
    cout << Pair<int, int>::getNumberOfPairs() << endl;
}
/** Expected output
1 3.1415
(1, 3.1415)
(3.1415, 1)
(1, 3)
1
0
 */