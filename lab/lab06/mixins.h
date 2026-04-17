
#include <iostream>
template<class ...Ts>
class Mixins : public Ts... {
public:
    Mixins(Ts&&... args) : Ts(std::forward<Ts>(args))... {}
    Mixins(const Ts&... args) : Ts(args)... {}
};