#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <numeric> 
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

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator(T* p) : ptr(p) {}

        reference  operator*()  const { return *ptr; }
        pointer    operator->() const { return  ptr; }

        iterator& operator++()    { ++ptr; return *this; }
        iterator  operator++(int) { iterator tmp = *this; ++ptr; return tmp; }

        bool operator==(const iterator& o) const { return ptr == o.ptr; }
        bool operator!=(const iterator& o) const { return ptr != o.ptr; }

    private:
        T* ptr;
    };

    struct const_iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator(const T* p) : ptr(p) {}
        const_iterator(const iterator& it) : ptr(&(*it)) {}

        reference  operator*()  const { return *ptr; }
        pointer    operator->() const { return  ptr; }

        const_iterator& operator++()    { ++ptr; return *this; }
        const_iterator  operator++(int) { const_iterator tmp = *this; ++ptr; return tmp; }

        bool operator==(const const_iterator& o) const { return ptr == o.ptr; }
        bool operator!=(const const_iterator& o) const { return ptr != o.ptr; }

    private:
        const T* ptr;
    };

    struct row_iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        row_iterator(T* p) : ptr(p) {}

        reference  operator*()  const { return *ptr; }
        pointer    operator->() const { return  ptr; }

        row_iterator& operator++()    { ++ptr; return *this; }
        row_iterator  operator++(int) { row_iterator tmp = *this; ++ptr; return tmp; }

        bool operator==(const row_iterator& o) const { return ptr == o.ptr; }
        bool operator!=(const row_iterator& o) const { return ptr != o.ptr; }

    private:
        T* ptr;
    };

    struct col_iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        col_iterator(T* p, size_t stride) : ptr(p), stride(stride) {}

        reference  operator*()  const { return *ptr; }
        pointer    operator->() const { return  ptr; }

        col_iterator& operator++()    { ptr += stride; return *this; }
        col_iterator  operator++(int) { col_iterator tmp = *this; ptr += stride; return tmp; }

        bool operator==(const col_iterator& o) const { return ptr == o.ptr; }
        bool operator!=(const col_iterator& o) const { return ptr != o.ptr; }

    private:
        T*     ptr;
        size_t stride;
    };

    iterator       begin()       { return iterator(data); }
    iterator       end()         { return iterator(data + N * M); }

    const_iterator begin() const { return const_iterator(data); }
    const_iterator end()   const { return const_iterator(data + N * M); }


    row_iterator row_begin(int n) { return row_iterator(data + (n - 1) * M); }
    row_iterator row_end  (int n) { return row_iterator(data + (n - 1) * M + M); }

    col_iterator col_begin(int n) { return col_iterator(data + (n - 1),     M); }
    col_iterator col_end  (int n) { return col_iterator(data + (n - 1) + N * M, M); }
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