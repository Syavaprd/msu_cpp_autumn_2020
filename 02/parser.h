#include <iostream>
#include <string>
#include <cstddef>

using ontoken = void (*)(std::string& token);
using edge = void (*)();
using onint = void (*)(int token);

void intcallback(onint callback);

void strcallback(ontoken callback);

void startcallback(edge callback);

void finishcallback(edge callback);

void parse(const std::string& str);