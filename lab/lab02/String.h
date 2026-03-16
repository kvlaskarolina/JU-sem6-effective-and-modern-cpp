#include <iostream>
#include <algorithm>
#include "MyString.h"
using namespace std;

class String
{
    using string = emcpp::MyString;
    //    using string = std::string;
    shared_ptr<string> str;
    /// Store a pointer to dynamically allocated string!

public:
    String() : str(std::make_shared<string>()) {} /// creates an empty string - DONE
    String(const char *str)
    {
        this->str = std::make_shared<string>(str);
    } /// copy C-string - DONE
    String(const String &s)
    {
        this->str = s.str;
    } /// no copy - DONE

    String &operator=(const String &s)
    {
        if (this != &s)
            str = s.str;
        return *this;
    }
    /// no copy
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch)
    {
        if (str.use_count() > 1)
        {
            str = std::make_shared<string>(*str);
        }
        (*str)[index] = ch;
    }
    /// no copy
    char get(int index) const
    {
        return (*str)[index];
    }
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b);
    friend ostream &operator<<(ostream &out, String s);
};

String operator+(String a, String b)
{
    if (a.str->empty())
        return b;
    if (b.str->empty())
        return a;
    String result;
    result.str = std::make_shared<String::string>((a.str->c_str() + *b.str).c_str());
    return result;
}
ostream &operator<<(ostream &out, String s)
{
    out << *s.str;
    return out;
}