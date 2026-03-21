#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
class Printer
{
    ostream &out;
    string prefix;
    string postfix;

public:
    Printer(ostream &out, string prefix, string postfix) : out(out), prefix(prefix), postfix(postfix) {}
    template <typename T>
    void operator()(const T &x) const
    {
        out << prefix << x << postfix;
    }
};

int main()
{
    /// Creates unary functor that takes one argument x (of any type)
    /// and outputs to given stream x surrounded by given prefix na postfix
    /// e.g. in the following  [ x ]
    /// Hint: define function template.
    Printer printer(std::cout, "[ ", " ] ");
    printer("hello"); // [ hello ]
    std::cout << "\nv = ";
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), printer); // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]

    std::ofstream file("myFile.txt");
    Printer filePrinter(file, "- ", "\n");
    filePrinter(5);
    filePrinter("My text");
    return 0;
}
/** myFile.txt
- 5
- My text
*/