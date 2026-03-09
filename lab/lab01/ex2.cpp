/*
Implement move constructor and move assignment operator for class Matrix.
Instead of making a copy of data they should just move data pointer from the source object to the
destination object.
Make sure to leave source object in the correct state and that there are no leaks of resources.
Implement unary operator - that for given matrix A returns matrix -A.
Observe copy elision that omit copy and move constructors and resulting in zero-copy pass-byvalue semantics.
*/

#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(Matrix &&other) : row(other.row), col(other.col), data(other.data)
{
    cout << "Move constructor called\n";
    other.row = 0;
    other.col = 0;
    other.data = nullptr;
}
Matrix Matrix::operator-(Matrix &other) const
{
    cout << "Unary operator - called\n";
    Matrix result(other.row, other.col);
    for (int i = 0; i < other.row * other.col; i++)
        result.data[i] = -other.data[i];
    return result;
}
Matrix Matrix::operator-() const
{
    cout << "Unary operator2 - called\n";
    Matrix result(row, col);
    for (int i = 0; i < row * col; i++)
        result.data[i] = -data[i];
    return result;
}
Matrix &Matrix::operator=(Matrix &&other)
{
    cout << "Move assignment operator called\n";
    if (this == &other)
        return *this;
    delete[] data;
    row = other.row;
    col = other.col;
    data = other.data;
    other.row = 0;
    other.col = 0;
    other.data = nullptr;
    return *this;
}