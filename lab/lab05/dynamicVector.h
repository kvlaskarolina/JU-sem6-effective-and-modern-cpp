#include "staticVector.h"

template <typename T>
class Vector<T, 0>
{
    T *data_;
    size_t size_;

public:
    using value_type = T;
    using size_type = std::size_t;
    typedef T *pointer;
    typedef T &reference;
    typedef const T &const_reference;

    Vector(size_type size) : size_(size)
    {
        data_ = new T[size_];
        for (size_type i = 0; i < size_; ++i)
        {
            data_[i] = T();
        }
    }
    Vector(const Vector &v) : size_(v.size_)
    {
        data_ = new T[size_];
        for (size_type i = 0; i < size_; ++i)
        {
            data_[i] = v.data_[i];
        }
    }
    Vector &operator=(const Vector &m)
    {
        if (this != &m)
        {
            if (size_ != m.size_)
            {
                delete[] data_;
                size_ = m.size_;
                data_ = new T[size_];
            }
            for (size_type i = 0; i < size_; ++i)
            {
                data_[i] = m.data_[i];
            }
        }
        return *this;
    }
    Vector(const std::initializer_list<T> &list) : size_(list.size())
    {
        data_ = new T[size_];
        size_type i = 0;
        for (const auto &elem : list)
        {
            data_[i++] = elem;
        }
    }
    template <size_t N>
    Vector(const Vector<T, N> &v) : size_(N)
    {
        data_ = new T[size_];
        for (size_type i = 0; i < size_; ++i)
        {
            data_[i] = v.data_[i];
        }
    }
    void resize(size_type new_size)
    {
        if (new_size != size_)
        {
            T *new_data = new T[new_size];
            for (size_type i = 0; i < std::min(size_, new_size); ++i)
            {
                new_data[i] = data_[i];
            }
            for (size_type i = size_; i < new_size; ++i)
            {
                new_data[i] = T();
            }
            delete[] data_;
            data_ = new_data;
            size_ = new_size;
        }
    }
    friend Vector operator+(const Vector &u, const Vector &v)
    {
        if (u.size_ != v.size_)
        {
            throw std::runtime_error("incompatible sizes in Vector::operator+");
        }
        Vector result(u.size_);
        for (size_type i = 0; i < u.size_; ++i)
        {
            result.data_[i] = u.data_[i] + v.data_[i];
        }
        return result;
    }
    template <size_t N>
    friend Vector operator+(const Vector &u, const Vector<T, N> &v)
    {
        if (u.size_ != N)
        {
            throw std::runtime_error("incompatible sizes in Vector::operator+");
        }
        Vector result(u.size_);
        for (size_type i = 0; i < u.size_; ++i)
        {
            result.data_[i] = u.data_[i] + v[i];
        }
        return result;
    }
    friend std::ostream &operator<<(std::ostream &out, const Vector &v)
    {
        for (size_type i = 0; i < v.size_; ++i)
        {
            out << v.data_[i];
            if (i + 1 < v.size_)
                out << " ";
        }
        return out;
    }

    reference operator[](size_type index)
    {
        return data_[index];
    }
    const_reference operator[](size_type index) const
    {
        return data_[index];
    }
    const_reference get(size_type index) const
    {
        return data_[index];
    }
    int size() const
    {
        return size_;
    }
};

// TODO operator +
/*
Operator+ should throw an exception if sizes do not match. The exception should be of a user
defined type VectorException that is derived from runtime_error.
*/