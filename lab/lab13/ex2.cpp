
#include <array>
#include <iostream>
#include <cmath>


/** 
 * Exercise 2a: 
 * Implement function power that computes x^n 
 * during compilation using recurrent formula
   x^2n = (x^n)^2
   x^2n+1 = (x^2n)*x
  */
 consteval auto power(auto x, int n) {
    if (n == 0) return decltype(x){1};          
    if (n % 2 == 0) {                           
        auto half = power(x, n / 2);
        return half * half;
    }                                           
    return power(x, n - 1) * x;
}



constinit double fiveToPowerFour = power(5, 4);

/**
 *  Exercise 2b:
 * Implement function generate_triangle that during compilation 
 * generates the Pascal trriangle of the given size N.
 * Pascal triangle
 * https://en.wikipedia.org/wiki/Pascal%27s_triangle
 *  
 */


 template <size_t N>
 class PascalTriangle {
     std::array<std::array<int, N>, N> data{};
 
 public:
     constexpr PascalTriangle() {
         for (size_t row = 0; row < N; ++row) {
             data[row][0] = 1;                   
             for (size_t col = 1; col <= row; ++col)
                 data[row][col] = data[row-1][col-1] + data[row-1][col];
         }
     }
 
     constexpr int operator()(size_t n, size_t m) const {
         return data[n][m];
     }
 };
 
 template <auto N>
 constexpr PascalTriangle<N> generatePascalTriangle() {
     return {};
 }
 
 constexpr size_t n = 10;
 constexpr auto triangle = generatePascalTriangle<n>();




int main(){

  static_assert(triangle(0,0) == 1);
  static_assert(triangle(5,3) == 10);
  static_assert(triangle(9,4) == 126);

  static_assert(power(5, 4)  == 625);
    static_assert(power(2, 10) == 1024);
    static_assert(power(3, 0)  == 1);

}