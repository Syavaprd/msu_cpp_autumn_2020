#include "parser.h"
#include <sstream>
#include <cassert>

std::ostringstream got_res;

void Begin() {
    got_res << "start parse\n";
}

void End() {
    got_res << "\nfinish parse\n";
}

void intdetect(int n) {
    got_res << n << " ";
}

void strdetect(std::string& n) {
    got_res << n << " ";
}

int main() {
    intcallback(intdetect);
    strcallback(strdetect);
    startcallback(Begin);
    finishcallback(End);
    std::string needed_res = "";
    needed_res = "start parse\nasfdf asd 12343 IOKLasfd 1009 2020 Se8va \nfinish parse\n";
    parse("asfdf asd\n12343\tIOKLasfd 1009 2020 Se8va ");
    assert (needed_res == got_res.str());
    got_res.str("");
    got_res.clear();
    needed_res = "start parse\nASD asd 123 567 A54 \nfinish parse\n";
    parse("ASD asd 123 567 A54");
    assert(needed_res == got_res.str());
    return 0;
}