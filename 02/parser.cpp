#include "parser.h"

onint inttoken = nullptr;
ontoken strtoken = nullptr;
edge start = nullptr;
edge finish = nullptr;

void intcallback(onint callback) {
    inttoken = callback;
}

void strcallback(ontoken callback) {
    strtoken = callback;
}

void startcallback(edge callback) {
    start = callback;
}

void finishcallback(edge callback) {
    finish = callback;
}

bool check_token(std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
void parse(const std::string& str) {
    if (start != nullptr) start();
    size_t pos_1 = 0;
    size_t found;
    std::string token;
    bool flag = true;
    while ((found = str.find_first_of(" \n\t", pos_1)) != std::string::npos) {
        token = str.substr(pos_1, found - pos_1);
        if (check_token(token) && (inttoken != nullptr)) {
            int number = std::stoi(token.c_str());
            inttoken(number);
        }
        else if (strtoken != nullptr) strtoken(token);
        pos_1 = str.find_first_not_of(" \n\t", found);
    }
    if (pos_1 == std::string::npos) {
        if (finish != nullptr) finish();
        return;
    }
    token = str.substr(pos_1);
    if (check_token(token) && (inttoken != nullptr)) {
        int number = std::stoi(token.c_str());
        inttoken(number);
    }
    else if (strtoken != nullptr) strtoken(token);
    if (finish != nullptr) finish();
}