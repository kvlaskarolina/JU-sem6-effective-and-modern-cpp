#pragma once
#include <vector>
#include <tuple>
#include <iostream>

template <typename T, typename... Ts>
struct index_of;

template <typename T, typename First, typename... Rest>
struct index_of<T, First, Rest...> {
    static constexpr std::size_t value = 1 + index_of<T, Rest...>::value;
};

template <typename T, typename... Rest> 
struct index_of<T, T, Rest...> {
    static constexpr std::size_t value = 0;
};


template <typename T, typename... Ts>
struct mv_is_one_of : std::false_type {};

template <typename T, typename First, typename... Rest>
struct mv_is_one_of<T, First, Rest...>
    : std::conditional_t<std::is_same<T, First>::value,
                         std::true_type,
                         mv_is_one_of<T, Rest...>> {};

template <typename... Types>
class MultiVector {
    static_assert(sizeof...(Types) > 0, "MultiVector requires at least one type");

    using Storage = std::tuple<std::vector<Types>...>;
    Storage storage_;

    template <std::size_t I>
    void print_one() const {
        std::cout << "[ ";
        for (const auto& v : std::get<I>(storage_))
            std::cout << v << ' ';
        std::cout << ']';
    }

    template <std::size_t... Is>
    void print_impl(std::index_sequence<Is...>) const {
        bool first = true;
        ((void)(first ? (void)(first = false) : (void)(std::cout << ' '),
                print_one<Is>()), ...);
        std::cout << '\n';
    }

public:
    template <typename T>
    void push_back(T&& value) {
        using D = std::decay_t<T>;
        static_assert(mv_is_one_of<D, Types...>::value,
                      "Type not in MultiVector's type list");
        constexpr std::size_t I = index_of<D, Types...>::value;
        std::get<I>(storage_).push_back(std::forward<T>(value));
    }

    void print() const {
        print_impl(std::index_sequence_for<Types...>{});
    }

    template <typename T>
    std::vector<T>& get() {
        static_assert(mv_is_one_of<T, Types...>::value,
                      "Type not in MultiVector's type list");
        return std::get<index_of<T, Types...>::value>(storage_);
    }

    template <typename T>
    const std::vector<T>& get() const {
        static_assert(mv_is_one_of<T, Types...>::value,
                      "Type not in MultiVector's type list");
        return std::get<index_of<T, Types...>::value>(storage_);
    }

    template <typename T>
    std::size_t size() const { return get<T>().size(); }

    std::size_t total_size() const {
        return total_size_impl(std::index_sequence_for<Types...>{});
    }

private:
    template <std::size_t... Is>
    std::size_t total_size_impl(std::index_sequence<Is...>) const {
        std::size_t n = 0;
        ((n += std::get<Is>(storage_).size()), ...);
        return n;
    }
};