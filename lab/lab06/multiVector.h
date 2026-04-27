#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>

template<typename Target, typename... Pack>
constexpr std::size_t indexOfFirst() {
    std::size_t i = 0;
    bool found = false;
    ((std::is_same_v<Target, Pack> 
        ? (found ? (void)0 : (void)(found = true))
        : (void)++i), ...);
    return i;
}

template<class... Types>
class MultiVector {
    std::tuple<std::vector<Types>...> data_;
public:
template<typename T>
void push_back(T&& value) {
    using DecayedT = std::decay_t<T>;
    constexpr std::size_t idx = indexOfFirst<std::vector<DecayedT>,
                                             std::vector<Types>...>();
    using VecType = std::tuple_element_t<idx, std::tuple<std::vector<Types>...>>;
    using ElemType = typename VecType::value_type;
    std::get<idx>(data_).push_back(static_cast<ElemType>(std::forward<T>(value)));
}

    void print() const {
        printImpl(std::index_sequence_for<Types...>{});
    }

private:
    template<std::size_t... Is>
    void printImpl(std::index_sequence<Is...>) const {
        ((std::cout << "[ " << printVector(std::get<Is>(data_)) << "] "), ...);
        std::cout << std::endl;
    }

    template<typename T>
    std::string printVector(const std::vector<T>& vec) const {
        std::ostringstream oss;
        for (const auto& elem : vec) {
            oss << elem << " ";
        }
        return oss.str();
    }
};