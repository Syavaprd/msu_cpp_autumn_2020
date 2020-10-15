#include <cassert>
#include "allocator.hpp"

void Tests() {
    std::cout << "Тесты начались" << std::endl;
    Allocator check;
    check.makeAllocator(50);
    assert(NULL == check.alloc(51));
    check.reset();
    assert(NULL != check.alloc(50));
    assert(NULL != check.alloc(0));
    assert(NULL != check.alloc(0));
    assert(NULL == check.alloc(1));
    check.reset();
    assert(NULL != check.alloc(10));
    assert(NULL != check.alloc(10));
    assert(NULL != check.alloc(10));
    assert(NULL != check.alloc(10));
    assert(NULL != check.alloc(10));
    assert(NULL == check.alloc(10));
    check.makeAllocator(5);
    assert(NULL != check.alloc(2));
    assert(NULL != check.alloc(2));
    assert(NULL != check.alloc(1));
    assert(NULL == check.alloc(1));
    check.reset();
    assert(NULL != check.alloc(5));
    assert(NULL == check.alloc(1));
    check.reset();
    assert(NULL == check.alloc(6));
    std::cout << "Тесты прошли успешно" << std::endl;
}

int main() {
    Tests();
    return 0;
}