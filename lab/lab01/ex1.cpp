#include <iostream>
using namespace std;

class Matrix
{
private:
    int row;
    int col;
    double *data;

public:
    Matrix() : row(0), col(0), data(nullptr)
    {
        cout << "Default constructor called\n";
    }
    Matrix(int row, int col) : row(row), col(col)
    {
        cout << "Matrix constructor called\n";
        data = new double[row * col];
    }
    Matrix(initializer_list<initializer_list<double>> init)
    {
        cout << "Initializer list constructor called\n";
        row = init.size();
        col = init.begin()->size();
        data = new double[row * col];
        int i = 0;
        for (const auto &r : init)
        {
            int j = 0;
            for (const auto &c : r)
            {
                data[i * col + j] = c;
                j++;
            }
            i++;
        }
    }
    Matrix(const Matrix &other) : row(other.row), col(other.col)
    {
        cout << "Copy constructor called\n";
        data = new double[row * col];
        for (int i = 0; i < row * col; i++)
        {
            data[i] = other.data[i];
        }
    }
    ~Matrix()
    {
        cout << "Destructor called\n";
        delete[] data;
    }
};
