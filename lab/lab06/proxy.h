#pragma once
#include <iostream>
#include <typeinfo>
#include <utility>
#include <cxxabi.h>  
#include <cstdlib>    

namespace detail {
inline std::string demangle(const char* mangled)
{
    int status = 0;
    char* buf = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
    std::string result = (status == 0 && buf) ? buf : mangled;
    std::free(buf);
    return result;
}
} 
inline void showNamesImpl(int) {}

template <typename Head, typename... Tail>
void showNamesImpl(int index, Head&& head, Tail&&... tail)
{
    std::string pretty = detail::demangle(typeid(head).name());
    const char*  mangled = typeid(head).name();
    std::cout << " " << index << " > " << pretty
              << " [" << mangled << "] = " << std::forward<Head>(head) << "\n";
    showNamesImpl(index + 1, std::forward<Tail>(tail)...);
}

template <typename... Args>
void showNames(Args&&... args)
{
    showNamesImpl(1, std::forward<Args>(args)...);
}

template <typename F>
class Proxy
{
public:
    explicit Proxy(F f) : functor_(std::move(f)) {}

    template <typename... Args>
    typename std::result_of<F(Args&&...)>::type
    operator()(Args&&... args)
    {
        std::cout << "\nProxy\n";
        showNames(std::forward<Args>(args)...);        
        return functor_(std::forward<Args>(args)...);   
    }

private:
    F functor_;
};

template <typename F>
Proxy<typename std::decay<F>::type> make_proxy(F&& f)
{
    return Proxy<typename std::decay<F>::type>(std::forward<F>(f));
}