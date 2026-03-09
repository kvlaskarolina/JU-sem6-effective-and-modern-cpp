/*
Implement class MatrixWithLabel that is a subclass of Matix and add field that stores matrix label
(as string, default value “A”). Class MatrixWithLabel should inherit all constructors from Matrix
(not reimplement them!) and add two new constructors:
MatrixWithLabel(label, numberOfRows, numberOfColumns)
MatrixWithLabel(label, initializer_list<...>)
Add also getLabel and setLabel methods.
*/
#include "matrix.h"
#include <iostream>
using namespace std;

MatrixWithLabel::MatrixWithLabel(string label, int numberOfRows, int numberOfColumns) : Matrix(numberOfRows, numberOfColumns), label(label)
{
    cout << "MatrixWithLabel constructor called\n";
}
MatrixWithLabel::MatrixWithLabel(string label, initializer_list<initializer_list<double>> init) : Matrix(init), label(label)
{
    cout << "MatrixWithLabel initializer list constructor called\n";
}
string MatrixWithLabel::getLabel() const
{
    return label;
}
void MatrixWithLabel::setLabel(string label)
{
    this->label = label;
}