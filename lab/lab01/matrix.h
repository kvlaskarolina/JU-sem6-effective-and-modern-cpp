#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;

class Matrix
{
private:
    int row, col;
    double *data;

public:
    Matrix();
    Matrix(int row, int col);
    Matrix(initializer_list<initializer_list<double>> init);
    Matrix(const Matrix &other);
    ~Matrix();

    Matrix &operator=(const Matrix &other);
    const double &operator()(int i, int j) const;
    friend ostream &operator<<(ostream &os, const Matrix &m);
    Matrix(Matrix &&other);
    Matrix operator-(Matrix &other) const;
    Matrix operator-() const;
    Matrix &operator=(Matrix &&other);
};

class MatrixWithLabel : public Matrix
{
private:
    string label = "A";

public:
    using Matrix::Matrix;
    MatrixWithLabel(string label, int numberOfRows, int numberOfColumns);
    MatrixWithLabel(string label, initializer_list<initializer_list<double>> init);
    string getLabel() const;
    void setLabel(string label);
};

#endif