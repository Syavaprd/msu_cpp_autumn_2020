#include <iostream>
#include "format.h"
#include <cassert>

int main()
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    bool caught;
    caught = false;
    try {
        text = format("{}", 0);
    }
    catch (const MyError&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("}", 0);
    }
    catch (const MyError&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{{}}", 0);
    }
    catch (const MyError&){
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        text = format("{1} {0}", 0);
    }
    catch (const MyError&){
        caught = true;
    }
    assert(caught);
    std::cout << "OK" << std::endl;
    return 0;
}