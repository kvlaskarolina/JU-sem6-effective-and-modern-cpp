#include <iostream>
#include <cmath>
using namespace std;

double sqrtn(int n, double x)
{
    return exp(log(x) / n);
}
double power(double x, double y)
{
    return exp(log(x) * y);
}

typedef double (*FP1)(int, double);
typedef double (*FP2)(double, double);

double compute(int n, double y, double z, FP1 f, FP2 g)
{
    return (f(n, y) > z) ? g(z, y) : g(y, z);
}

int main()
{
    FP1 fp1 = sqrtn;
    FP2 fp2 = power;
    double (*fp3)(int, double, double, FP1, FP2) = compute;

    cout << fp3(2, 10, 3, fp1, fp2) << endl;
    cout << fp3(3, 10, 3, fp1, fp2) << endl;
    return 0;
}