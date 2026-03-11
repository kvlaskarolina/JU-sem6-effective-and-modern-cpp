#pragma once
#include <iostream>
#include "Box.h"

class Container : public Box
{
public:
    static bool verbose;
    Container(int content) : Box(content) {};

    Container(const Container &container) = delete;            // disable copy constructor
    Container &operator=(const Container &container) = delete; // disable copy assignment

    Container(Container &&container) = default;            // enable move constructor
    Container &operator=(Container &&container) = default; // enable move assignment
    ~Container() = default;                                // enable destructor

    friend Container operator+(const Container &p1, const Container &p2);
    friend std::ostream &operator<<(std::ostream &out, const Container &p)
    {
        return (out << " [" << p.getContent() << "] ");
    }
};
bool Container::verbose = false;

inline Container operator+(const Container &p1, const Container &p2)
{
    Container suma(p1.getContent() + p2.getContent());
    return suma;
}