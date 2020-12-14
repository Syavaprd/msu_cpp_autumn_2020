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
    got_res << "Got int token " << n << " ";
}

void strdetect(std::string& n) {
    got_res << "Got string token " << n << " ";
}

int main() {
    intcallback(intdetect);
    strcallback(strdetect);
    startcallback(Begin);
    finishcallback(End);
    std::string needed_res = "";
    needed_res = "start parse\nGot string token asfdf Got string token asd Got int token 12343 Got string token IOKLasfd Got int token 1009 Got int token 2020 Got string token Se8va \nfinish parse\n";
    parse("asfdf asd\n12343\tIOKLasfd 1009 2020 Se8va ");
    assert (needed_res == got_res.str());
    got_res.str("");

    got_res.clear();
    needed_res = "start parse\nGot string token 1bc Got string token ASD Got string token asd Got int token 123 Got int token 567 Got string token A54 \nfinish parse\n";
    parse("1bc ASD asd 123 567 A54");
    assert(needed_res == got_res.str());
    return 0;
}