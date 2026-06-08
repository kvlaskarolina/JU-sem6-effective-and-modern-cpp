
export module emcpp.vector;

import <iostream>;
import <initializer_list>;
import <algorithm>;
import <utility>;
import <type_traits>;
import <string>;
import <stdexcept>;

export namespace emcpp {

    struct FastPolicy {
        static void check_bounds(int i, int N) {}
    };

    struct SafePolicy {
        static void check_bounds(int i, int N) {
            if (i < 0 || i >= N) {
                throw std::out_of_range("Vector index out of bounds!");
            }
        }
    };

    template <typename T>
    struct VectorTraits {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
    };

    template <typename T, typename L, typename R>
    struct VecAdd {
        L lhs; R rhs;
        VecAdd(L&& l, R&& r) : lhs(std::forward<L>(l)), rhs(std::forward<R>(r)) {}
        auto operator[](int i) const { return lhs[i] + rhs[i]; }
    };

    template <typename T, typename L, typename R>
    struct VecSub {
        L lhs; R rhs;
        VecSub(L&& l, R&& r) : lhs(std::forward<L>(l)), rhs(std::forward<R>(r)) {}
        auto operator[](int i) const { return lhs[i] - rhs[i]; }
    };

    template <typename T, typename R>
    struct VecScalarMul {
        int scalar; R rhs;
        VecScalarMul(int s, R&& r) : scalar(s), rhs(std::forward<R>(r)) {}
        auto operator[](int i) const { return scalar * rhs[i]; }
    };

    template <typename T, int N, typename Policy = FastPolicy, typename Traits = VectorTraits<T>>
    class Vector {
        T data[N];

        template<typename Expr>
        using IsNotVector = std::enable_if_t<
            !std::is_same_v<typename std::decay_t<Expr>, Vector>>;

    public:
        using value_type = typename Traits::value_type;

        Vector() {
            for (int i = 0; i < N; ++i) data[i] = T{};
            std::cout << " Default constr\n";
        }

        Vector(std::initializer_list<T> list) {
            std::cout << " Init list constr\n";
            auto it = list.begin();
            for (int i = 0; i < N; ++i)
                data[i] = (it != list.end()) ? *it++ : T{};
        }

        Vector(const Vector& other) {
            std::copy(other.data, other.data + N, data);
            std::cout << " Copy constr\n";
        }

        Vector(Vector&& other) noexcept {
            std::move(other.data, other.data + N, data);
            std::cout << " Move constr\n";
        }

        template <typename Expr, typename = IsNotVector<Expr>>
        Vector(Expr&& expr) {
            std::cout << " Expr constr\n";
            for (int i = 0; i < N; ++i)
                data[i] = expr[i];
        }

        template <typename Expr, typename = IsNotVector<Expr>>
        Vector& operator=(Expr&& expr) {
            for (int i = 0; i < N; ++i)
                data[i] = expr[i];
            return *this;
        }

        typename Traits::const_reference operator[](int i) const { 
            Policy::check_bounds(i, N);
            return data[i]; 
        }
        
        typename Traits::reference operator[](int i) { 
            Policy::check_bounds(i, N);
            return data[i]; 
        }

        friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
            for (int i = 0; i < N; ++i)
                out << v.data[i] << (i == N - 1 ? "" : ", ");
            return out;
        }
    };

    export template <typename T, typename L, typename R>
    auto operator+(L&& lhs, R&& rhs) {
        return VecAdd<T, std::decay_t<L>, std::decay_t<R>>(std::forward<L>(lhs), std::forward<R>(rhs));
    }

    export template <typename T, typename L, typename R>
    auto operator-(L&& lhs, R&& rhs) {
        return VecSub<T, std::decay_t<L>, std::decay_t<R>>(std::forward<L>(lhs), std::forward<R>(rhs));
    }

    export template <typename T, typename R>
    auto operator*(int s, R&& expr) {
        return VecScalarMul<T, std::decay_t<R>>(s, std::forward<R>(expr));
    }
}

export extern template class emcpp::Vector<int, 10, emcpp::SafePolicy>;
export extern template class emcpp::Vector<double, 10, emcpp::SafePolicy>;
export extern template class emcpp::Vector<std::string, 3, emcpp::SafePolicy>;