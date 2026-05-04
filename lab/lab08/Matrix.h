#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix {

    T data[N * M];

public:
    constexpr size_t numberOfRows()    const noexcept { return N; }
    constexpr size_t numberOfColumns() const noexcept { return M; }

    constexpr explicit Matrix(T initValue = T{}) noexcept {
        for (size_t i = 0; i < N * M; ++i)
            data[i] = initValue;
    }

    constexpr Matrix(const std::initializer_list<std::initializer_list<T>>& list) noexcept
        : data{}
    {
        size_t i = 0;
        for (const auto& row : list) {
            if (i >= N) break;
            size_t j = 0;
            for (const auto& val : row) {
                if (j >= M) break;
                data[i * M + j] = val;
                ++j;
            }
            ++i;
        }
    }

    constexpr Matrix(const Matrix& m) noexcept {
        for (size_t i = 0; i < N * M; ++i)
            data[i] = m.data[i];
    }

    constexpr Matrix& operator=(const Matrix& m) noexcept {
        if (&m != this)
            for (size_t i = 0; i < N * M; ++i)
                data[i] = m.data[i];
        return *this;
    }

    constexpr T& operator()(int i, int j) noexcept {
        return data[(i - 1) * M + j - 1];
    }

    constexpr const T& operator()(int i, int j) const noexcept {
        return data[(i - 1) * M + j - 1];
    }

    friend constexpr Matrix operator+(const Matrix& a, const Matrix& b) noexcept {
        Matrix r;
        for (int i = 1; i <= (int)N; ++i)
            for (int j = 1; j <= (int)M; ++j)
                r(i, j) = a(i, j) + b(i, j);
        return r;
    }
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M>& m, int width = 10) {
    for (int i = 1; i <= (int)m.numberOfRows(); ++i) {
        for (int j = 1; j <= (int)m.numberOfColumns(); ++j) {
            if (j != 1) cout << " ";
            cout << setw(width) << m(i, j);
        }
        cout << "\n";
    }
}