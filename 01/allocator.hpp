#pragma once
#include <iostream>
#include <cstdio>

class Allocator {
public:
    void makeAllocator(size_t volume) {
        if (begin != nullptr) {
            delete [] begin;
            offset = 0;
        }
        capacity = volume;
        begin = new char[capacity];
        return ;
    }

    ~Allocator() {
        delete [] begin;
    }

    char* alloc(size_t size) {
        if (size > capacity - offset) {
            return nullptr;
        }
        char *new_offset = begin + offset;
        offset += size;
        return new_offset;
    }

    void reset() {
        offset = 0;
        return ;
    }

private:
    size_t capacity = 0, offset = 0;
    char *begin = nullptr;
};