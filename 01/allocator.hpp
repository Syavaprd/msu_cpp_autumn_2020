#pragma once
#include <iostream>
#include <cstdio>

class Allocator {
public:
    void makeAllocator(size_t capacity_) {
        capacity = capacity_;
        if (begin != NULL) {
            delete [] begin;
            offset = 0;
            capacity = 0;
        }
        capacity = capacity_;
        begin = new char[capacity];
        return ;
    }

    ~Allocator() {
        delete [] begin;
    }

    char* alloc(size_t size) {
        if (size > capacity - offset) {
            return NULL;
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
    char *begin = NULL;
};