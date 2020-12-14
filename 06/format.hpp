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

    const char* what() const noexcept override {
        return err.c_str();
    }
};

template<class T> 
std::string to_string(const T & obj){
    std::stringstream str;
    str << obj;
    return str.str();
}

std::string format(const std::string & str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '{' || str[i] == '}')
            throw MyError("", i + 1);
    }
    return str;
}

template<class ... Args> std::string format(const std::string & str, const Args& ... args){
    std::vector<std::string> strings {to_string((args))...};
    bool fmt = false;
    bool nothing;
    unsigned long id;
    std::string value;
    std::string  format_string = "";
    for(int i = 0; i < str.length(); i++) {
        if(fmt) 
            if(str[i] == '}')
                if(nothing || id >= strings.size())
                    throw MyError("", i + 1);
                else {
                    format_string += strings[id];
                    fmt = false;
                }
            else {
                while((str[i] != '}') && (i != str.length() - 1)) {
                    if(std::isdigit(str[i])) {
                        value += str[i];
                    }
                    else
                        throw MyError("", i + 1);
                    ++i;
                }
                --i;
                nothing = false;
                try {
                    id = std::stoul(value);
                } catch(const std::logic_error& e) {
                    throw MyError("", i + 1);
                }
            }
        else
            if(str[i] == '{') {
                fmt = true;
                nothing = true;
                id = 0;
                value = "";
            }
            else if(str[i] == '}')
                throw MyError("", i + 1);
            else 
                format_string += str[i];
    }
    if(fmt)
        throw MyError("", 0);
    return format_string;
}