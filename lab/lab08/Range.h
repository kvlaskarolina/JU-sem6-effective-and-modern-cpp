

#ifndef LAB8_RANGE_H
#define LAB8_RANGE_H
#include <iostream>
#include <iterator>

template<typename T>
class RangeIterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const T*;
    using reference         = const T&;

    RangeIterator(T current, T stop, T step)
        : current_(current), stop_(stop), step_(step) {}

    reference operator*()  const { return current_; }
    pointer   operator->() const { return &current_; }

    RangeIterator& operator++()    { current_ += step_; return *this; }
    RangeIterator  operator++(int) { auto tmp = *this; ++(*this); return tmp; }

    bool operator==(const RangeIterator& other) const {
        if (step_ > T{0}) return current_ >= stop_ && other.current_ >= other.stop_;
        else               return current_ <= stop_ && other.current_ <= other.stop_;
    }
    bool operator!=(const RangeIterator& other) const { return !(*this == other); }

private:
    T current_, stop_, step_;
};

template<typename T>
class Range {
public:
    explicit Range(T stop)
        : start_(T{0}), stop_(stop), step_(T{1}) {}

    Range(T start, T stop, T step = T{1})
        : start_(start), stop_(stop), step_(step) {}

    RangeIterator<T> begin() const { return {start_, stop_, step_}; }
    RangeIterator<T> end()   const { return {stop_,  stop_, step_}; }

private:
    T start_, stop_, step_;
};


template<typename T>
Range<T> make_range(T start, T stop, T step = T{1}) {
    return Range<T>(start, stop, step);
}
template<typename T>
Range<T> make_range(T stop, T step = T{1}) {
    return Range<T>(T{0}, stop, step);
}
#endif //LAB8_RANGE_H
