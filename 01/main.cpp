#include <cassert>
#include "allocator.hpp"

void Tests() {
    std::cout << "Тесты начались" << std::endl;
    Allocator check;
    check.makeAllocator(50);
    assert(nullptr == check.alloc(51));
    check.reset();
    assert(nullptr != check.alloc(50));
    assert(nullptr != check.alloc(0));
    assert(nullptr != check.alloc(0));
    assert(nullptr == check.alloc(1));
    check.reset();
    assert(nullptr != check.alloc(10));
    assert(nullptr != check.alloc(10));
    assert(nullptr != check.alloc(10));
    assert(nullptr != check.alloc(10));
    assert(nullptr != check.alloc(10));
    assert(nullptr == check.alloc(10));
    check.makeAllocator(5);
    assert(nullptr != check.alloc(2));
    assert(nullptr != check.alloc(2));
    assert(nullptr != check.alloc(1));
    assert(nullptr == check.alloc(1));
    check.reset();
    assert(nullptr != check.alloc(5));
    assert(nullptr == check.alloc(1));
    check.reset();
    assert(nullptr == check.alloc(6));
    std::cout << "Тесты прошли успешно" << std::endl;
}

int main() {
    Tests();
    return 0;
}