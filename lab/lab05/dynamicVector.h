#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include "staticVector.h"  
template <typename T>
class Vector<T, 0> {
    size_t  size_;
    T      *data_;

public:
    using value_type      = T;
    using size_type       = std::size_t;
    typedef T*       pointer;
    typedef T&       reference;
    typedef const T& const_reference;

    explicit Vector(size_type size) : size_(size), data_(new T[size]) {
        for (size_type i = 0; i < size_; ++i)
            data_[i] = T();
    }

    Vector(const Vector &v) : size_(v.size_), data_(new T[v.size_]) {
        for (size_type i = 0; i < size_; ++i)
            data_[i] = v.data_[i];
    }

    Vector(const std::initializer_list<T> &list)
        : size_(list.size()), data_(new T[list.size()])
    {
        size_type i = 0;
        for (const auto &elem : list)
            data_[i++] = elem;
    }

    // static -> dynamic
    template <size_t N>
    explicit Vector(const Vector<T, N> &v) : size_(N), data_(new T[N]) {
        for (size_type i = 0; i < size_; ++i)
            data_[i] = v[i];
    }

    Vector(Vector &&other) noexcept
    : size_(other.size_), data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;  
    }

    Vector &operator=(Vector &&other) noexcept {
        if (this != &other) {
            delete[] data_;      
            size_       = other.size_;
            data_       = other.data_;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~Vector() { delete[] data_; }

    Vector &operator=(const Vector &m) {
        if (this != &m) {
            if (size_ != m.size_) {
                delete[] data_;
                size_  = m.size_;
                data_  = new T[size_];
            }
            for (size_type i = 0; i < size_; ++i)
                data_[i] = m.data_[i];
        }
        return *this;
    }

    void resize(size_type new_size) {
        if (new_size != size_) {
            T *new_data = new T[new_size];
            for (size_type i = 0; i < std::min(size_, new_size); ++i)
                new_data[i] = data_[i];
            for (size_type i = size_; i < new_size; ++i)
                new_data[i] = T();
            delete[] data_;
            data_ = new_data;
            size_ = new_size;
        }
    }

    reference       operator[](size_type index)       { return data_[index]; }
    const_reference operator[](size_type index) const { return data_[index]; }
    const_reference get(size_type index)        const { return data_[index]; }

    size_type size() const { return size_; }

    friend Vector operator+(const Vector &u, const Vector &v) {
        if (u.size_ != v.size_)
            throw VectorException("incompatible sizes in Vector::operator+");
        Vector result(u.size_);
        for (size_type i = 0; i < u.size_; ++i)
            result.data_[i] = u.data_[i] + v.data_[i];
        return result;
    }
    template <size_t N>
    friend Vector<T, N> operator+(const Vector &u, const Vector<T, N> &v) {
        if (u.size_ != N)
            throw VectorException("incompatible sizes in Vector::operator+");
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i)
            result[i] = u.data_[i] + v[i];
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &v) {
        for (size_type i = 0; i < v.size_; ++i) {
            out << v.data_[i];
            if (i + 1 < v.size_) out << " ";
        }
        return out;
    }
};

#endif // DYNAMIC_VECTOR_H