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
    Matrix(int row, int col) : row(row), col(col), data(new double[row * col]())
    {
        cout << "Matrix constructor called\n";
    }
    Matrix(initializer_list<initializer_list<double>> init)
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
    Matrix(const Matrix &other) : row(other.row), col(other.col), data(new double[other.row * other.col])
    {
        cout << "Copy constructor called\n";
        for (int i = 0; i < row * col; i++)
            data[i] = other.data[i];
    }
    ~Matrix()
    {
        cout << "Destructor called\n";
        delete[] data;
    }

    friend ostream &operator<<(ostream &os, const Matrix &m)
    {
        for (int i = 0; i < m.row; i++)
        {
            for (int j = 0; j < m.col; j++)
                os << m.data[i * m.col + j] << " ";
            os << '\n';
        }
        return os;
    }

    Matrix &operator=(const Matrix &other)
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

    const double &operator()(int i, int j) const
    {
        return data[(i - 1) * col + (j - 1)];
    }
};

int main()
{
    Matrix m1;                                              // default constructor: N=M=0, data=nullptr
    Matrix m2(3, 4);                                        // N = 3, M = 4, data = N*M doubles set to 0.0
    Matrix m3({{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}}); // from initializer_list
    cout << m2(1, 1) << endl;                               // 0 - the first element in data (we count from 1)
    cout << m3(2, 2) << endl;                               // 23
    cout << m3;                                             // prints matrix
    cout << "Copy semantics \n";
    Matrix m4 = m2; // copy constructor that makes deep copy of the matrix m2
    m4 = m3;        // copy assignment makes deep copy of the matrix m3
}
