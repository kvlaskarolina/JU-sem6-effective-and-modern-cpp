#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>
#include <algorithm>

template <typename T, size_t N> class Vector;
template <typename T>           class Vector<T, 0>;

class VectorException : public std::runtime_error {
public:
    explicit VectorException(const std::string &message)
        : std::runtime_error(message) {}
};

template <typename T, size_t N>
class Vector {
    T data_[N];

public:
    typedef T          value_type;
    typedef std::size_t size_type;
    typedef T*         pointer;
    typedef T&         reference;
    typedef const T&   const_reference;

    Vector() {
        for (size_type i = 0; i < N; ++i)
            data_[i] = T();
    }

    Vector(const Vector &v) {
        for (size_type i = 0; i < N; ++i)
            data_[i] = v.data_[i];
    }

    Vector(const std::initializer_list<T> &list) {
        assert(list.size() == N);
        size_type i = 0;
        for (const auto &elem : list)
            data_[i++] = elem;
    }

    // dynamic -> static
    explicit Vector(const Vector<T, 0> &v) {
        if (static_cast<size_type>(v.size()) != N)
            throw VectorException(
                "Size mismatch: cannot convert dynamic vector of size " +
                std::to_string(v.size()) +
                " to static vector of size " +
                std::to_string(N));
        for (size_type i = 0; i < N; ++i)
            data_[i] = v.get(i);
    }

    template <typename U>
    explicit Vector(const Vector<U, N> &other) {
        for (size_type i = 0; i < N; ++i)
            data_[i] = static_cast<T>(other[i]);
    }

    Vector &operator=(const Vector &m) {
        if (this != &m)
            for (size_type i = 0; i < N; ++i)
                data_[i] = m.data_[i];
        return *this;
    }

    reference       operator[](size_type index)       { return data_[index]; }
    const_reference operator[](size_type index) const { return data_[index]; }
    const_reference get(size_type index)        const { return data_[index]; }
    void            set(size_type index, const_reference value) { data_[index] = value; }

    constexpr size_type size() const { return N; }

    friend Vector operator+(const Vector &u, const Vector &v) {
        Vector result;
        for (size_type i = 0; i < N; ++i)
            result.data_[i] = u.data_[i] + v.data_[i];
        return result;
    }

    friend Vector operator+(const Vector &u, const Vector<T, 0> &v) {
        if (static_cast<size_type>(v.size()) != N)
            throw VectorException("incompatible sizes in Vector::operator+");
        Vector result;
        for (size_type i = 0; i < N; ++i)
            result.data_[i] = u.data_[i] + v.get(i);
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &v) {
        for (size_type i = 0; i < N; ++i) {
            out << v.data_[i];
            if (i + 1 < N) out << " ";
        }
        return out;
    }
};

#endif // STATIC_VECTOR_H