#pragma once

#include <iterator>
#include <type_traits>

template<typename C, typename P>
class Filter {
public:
    using Storage = std::conditional_t<
                        std::is_lvalue_reference<C>::value,
                        C,
                        std::remove_reference_t<C>>;

    using base_iter  = decltype(std::declval<std::remove_reference_t<C>&>().begin());
    using value_type = typename std::iterator_traits<base_iter>::value_type;

    Filter(C&& c, P p)
        : storage_(std::forward<C>(c)), pred_(std::move(p)) {}

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type        = Filter::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const value_type*;
        using reference         = const value_type&;

        iterator(base_iter cur, base_iter end, const P& pred)
            : cur_(cur), end_(end), pred_(pred)
        {
            skip();
        }

        reference operator*()  const { return *cur_; }
        pointer   operator->() const { return &(*cur_); }

        iterator& operator++() { ++cur_; skip(); return *this; }
        iterator  operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& o) const { return cur_ == o.cur_; }
        bool operator!=(const iterator& o) const { return cur_ != o.cur_; }

    private:
        void skip() {
            while (cur_ != end_ && !pred_(*cur_))
                ++cur_;
        }

        base_iter cur_;
        base_iter end_;
        const P&  pred_;
    };

    iterator begin() { return iterator(get().begin(), get().end(), pred_); }
    iterator end()   { return iterator(get().end(),   get().end(), pred_); }

private:
    Storage storage_;

    std::remove_reference_t<C>& get() { return storage_; }

    P pred_;
};

template<typename C, typename P>
auto make_filter(C&& c, P p) {
    return Filter<C, P>(std::forward<C>(c), std::move(p));
}
