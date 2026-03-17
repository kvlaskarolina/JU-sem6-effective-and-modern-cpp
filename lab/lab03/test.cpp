#include <iostream>
using namespace std;
void print(const std::vector<int> &v, const std::string &label = "")
{
    cout << label;
    for (auto x : v)
        cout << " " << x;
    cout << endl;
}
int main()
{
    std::vector<int> v = {-9, -3, 1, 6, 256, 64, 16 * 3, 16 * 9, 16, 8 * 7, -2, 5, 9, 0, -6, -4};

    int start = 5, step = 2;
    auto arithmeticGenerator = [current = start, &step]() mutable
    {
        int val = current;
        current += step;
        return val;
    };
    std::generate(v.begin(), v.end(), arithmeticGenerator);
    print(v, "arithm [5,2] :");

    v.resize(20);
    start = 0;
    step = 5;
    std::generate(v.begin(), v.end(), arithmeticGenerator);
    print(v, "arithm [5,5] :");

    /// 2. Sort in increasing order but
    ///  - negative numbers  are after positive ones, with zero in the middle,
    ///  - if numbers have the same sign then odd numbers are after even ones
    /// e.g.  4  < 8 < 1 < 3 < 0 <  -8 < -2 < -7 < -3
}