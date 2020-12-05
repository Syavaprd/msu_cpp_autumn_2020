#include "parser.h"


void Begin() {
    std::cout << "start parse\n";
}

void End() {
    std::cout << "\nfinish parse\n";
}

void intdetect(int n) {
    std::cout << n << " ";
}

void strdetect(std::string& n) {
    std::cout << n << " ";
}

int main() {
    intcallback(intdetect);
    strcallback(strdetect);
    startcallback(Begin);
    finishcallback(End);
    parse("asfdf asd\n12343\tIOKLasfd 1009 2020 Seva");
    return 0;
}