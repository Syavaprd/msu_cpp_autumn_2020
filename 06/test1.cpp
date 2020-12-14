#include <iostream>
#include "format.hpp"
#include <cassert>

int main(){
    bool caught = false;

    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    try {
        text = format("{", 0);
    }
    catch (const MyError&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{0", 0);
    }
    catch (const MyError&){
        caught = true;
    }
    assert(caught);
    std::cout << "OK" << std::endl;
    return 0;
}