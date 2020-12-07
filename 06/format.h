#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class MyError : public std::exception {
    size_t pos;
    std::string err;
public:
    MyError(const std::string& str, size_t p) : pos(p), err(str) {}
    ~MyError() = default;
    MyError() = default;

    MyError(const MyError&) = default;

    MyError& operator=(const MyError&) = default;

    size_t get_pos() const { return pos; }

    const char* what() const noexcept {
        return err.c_str();
    }
};

template<class T> std::string to_string(const T & obj){
    std::stringstream str;
    str << obj;
    return str.str();
}

std::string format(const std::string & str) {
    for(int i = 0; i < str.length(); i++) {
        if(str.data()[i] == '{' || str.data()[i] == '}')
            throw MyError("", i + 1);
    }
    return str;
}

template<class ... Args> std::string format(const std::string & str, Args&& ... args){
    std::vector<std::string> strings {to_string(std::forward<Args>(args))...};
    bool fmt = false;
    bool nothing;
    int id;
    std::string  format_string = "";
    for(int i = 0; i < str.length(); i++) {
        if(fmt) 
            if(str.data()[i] == '}')
                if(nothing || id >= strings.size())
                    throw MyError("", i + 1);
                else {
                    format_string += strings[id];
                    fmt = false;
                }
            else
                if(str.data()[i] <= '9' && str.data()[i] >= '0') {
                    nothing = false;
                    id += str.data()[i] - '0';
                }
                else
                    throw MyError("", i + 1);
        else
            if(str.data()[i] == '{') {
                fmt = true;
                nothing = true;
                id = 0;
            }
            else if(str.data()[i] == '}')
                throw MyError("", i + 1);
            else 
                format_string += str.data()[i];
    }
    if(fmt)
        throw MyError("", 0);
    return format_string;
}