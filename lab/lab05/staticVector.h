
#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T, size_t N>
class Vector
{
    T data[N];

public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef T *pointer;
    typedef T &reference;
    typedef const T &const_reference;

    Vector()
    {
        for (auto &elem : data)
        {
            elem = T();
        }
    }
    Vector(const Vector &v)
    {
        for (size_type i = 0; i < N; ++i)
        {
            data[i] = v.data[i];
        }
    }
    Vector &operator=(const Vector &m)
    {
        if (this != &m)
        {
            for (size_type i = 0; i < N; ++i)
            {
                data[i] = m.data[i];
            }
        }
        return *this;
    }
    Vector(const std::initializer_list<T> &list)
    {
        assert(list.size() == N);
        size_type i = 0;
        for (const auto &elem : list)
        {
            data[i++] = elem;
        }
    }
    Vector(const Vector<T, 0> &v)
    {
        assert(v.size() == N);
        for (size_type i = 0; i < N; ++i)
        {
            data[i] = v.get(i);
        }
    }

    friend Vector operator+(const Vector &u, const Vector &v)
    {
        Vector result;
        for (size_type i = 0; i < N; ++i)
        {
            result.data[i] = u.data[i] + v.data[i];
        }
        return result;
    }
    const_reference get(size_type index) const
    {
        return data[index];
    }
    friend Vector operator+(const Vector &u, const Vector<T, 0> &v)
    {
        assert(v.size() == N);
        Vector result;
        for (size_type i = 0; i < N; ++i)
        {
            result.data[i] = u.data[i] + v.data_[i];
        }
        return result;
    }

    constexpr size_type size() const
    {
        return N;
    }

    void set(size_type index, const_reference value)
    {
        data[index] = value;
    }

    reference operator[](size_type index)
    {
        return data[index];
    }
    const_reference operator[](size_type index) const
    {
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &v)
    {
        for (auto elem : v.data)
        {
            out << elem << " ";
        }
        return out;
    }
};

#endif // STATIC_VECTOR_H