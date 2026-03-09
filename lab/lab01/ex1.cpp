#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix() : row(0), col(0), data(nullptr)
{
    cout << "Default constructor called\n";
}
Matrix::Matrix(int row, int col) : row(row), col(col), data(new double[row * col]())
{
    cout << "Matrix constructor called\n";
}
Matrix::Matrix(initializer_list<initializer_list<double>> init)
{
    cout << "Initializer list constructor called\n";
    row = init.size();
    col = 0;
    for (const auto &r : init)
        col = max(col, (int)r.size());

    data = new double[row * col];
    int i = 0;
    for (const auto &r : init)
    {
        int j = 0;
        for (const auto &val : r)
        {
            data[i * col + j] = val;
            j++;
        }
        i++;
    }
}
Matrix::Matrix(const Matrix &other) : row(other.row), col(other.col), data(new double[other.row * other.col])
{
    cout << "Copy constructor called\n";
    for (int i = 0; i < row * col; i++)
        data[i] = other.data[i];
}
Matrix::~Matrix()
{
    cout << "Destructor called\n";
    delete[] data;
}

ostream &operator<<(ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.col; j++)
            os << m.data[i * m.col + j] << " ";
        os << '\n';
    }
    return os;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    cout << "Copy assignment operator called\n";
    if (this == &other)
        return *this;
    delete[] data;
    row = other.row;
    col = other.col;
    data = new double[row * col];
    for (int i = 0; i < row * col; i++)
        data[i] = other.data[i];
    return *this;
}
const double &Matrix::operator()(int i, int j) const
{
    return data[(i - 1) * col + (j - 1)];
}
