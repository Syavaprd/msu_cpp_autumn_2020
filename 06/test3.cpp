#include <iostream>
#include "format.h"
#include <cassert>

int main()
{
    auto text = format("{0}", 1);
    assert(text == "1");
    text = format("");
    assert(text == "");
    text = format("1");
    assert(text == "1");
    text = format("{0}{0}", "a");
    assert(text == "aa");
    std::cout << "OK" << std::endl;
    return 0;
}