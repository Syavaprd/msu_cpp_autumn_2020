#pragma once
#include <iostream>

template<class T>
class allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    using const_reference = const T&;

    pointer allocate(size_type count = 0);

    template<typename... Args>
    void construct(pointer ptr, Args&&... args) {
        ::new((void *)ptr) value_type(std::forward<Args>(args)...);
    }

    void deallocate(pointer ptr, size_type count);
    void destroy(pointer ptr);
};

template<class T>
T* allocator<T>::allocate(size_type count) {
    if(count)
        return static_cast<pointer>(::operator new(sizeof(value_type) * count));
    return nullptr;
}

/*template<class T>
void allocator<T>::construct(pointer ptr, const_reference val){
    new (ptr) value_type(val);
}*/



template<class T>
void allocator<T>::deallocate(pointer ptr, size_type count) {
    ::operator delete(ptr, sizeof(value_type) * count);
}

template<class T>
void allocator<T>::destroy(pointer ptr) {
    ptr->~value_type();
}



template <class T>
class Iterator{
    T* ptr;
    bool rev;

public:
    explicit Iterator(T* pointer, bool reverse = false);
    bool operator>(const Iterator<T> & other) const;
    bool operator<(const Iterator<T> & other) const;
    bool operator>=(const Iterator<T> & other) const;
    bool operator<=(const Iterator<T> & other) const;
    bool operator==(const Iterator<T> & other) const;
    bool operator!=(const Iterator<T> & other) const;
    Iterator<T>& operator++();
    Iterator<T>& operator--();
    Iterator<T> operator++(int);
    Iterator<T> operator--(int);
    Iterator<T>& operator+=(int n);
    Iterator<T>& operator-=(int n);
    Iterator<T> operator+(int n) const;
    template<class K>
    friend Iterator<K> operator+(long long n, const Iterator<K>& other);
    Iterator<T> operator-(int n) const;
    long long operator-(const Iterator<T>& other) const;
    T & operator*();
    const T & operator*() const;
    T & operator[](size_t n);
    const T & operator[](size_t n) const;
};

template <class T>
Iterator<T>::Iterator(T* pointer, bool reverse) {
    ptr = pointer;
    rev = reverse;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T> & other) const {
    return ptr == other.ptr;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T> & other) const {
    return !operator==(other);
}

template <class T>
bool Iterator<T>::operator>(const Iterator<T> & other) const {
    return (other < (*this));
}

template <class T>
bool Iterator<T>::operator<(const Iterator<T> & other) const {
    if(rev != other.rev)
        throw std::logic_error("");
    return ((*this) - other > 0);
}

template <class T>
bool Iterator<T>::operator>=(const Iterator<T> & other) const {
    return !((*this) < other);
}

template <class T>
bool Iterator<T>::operator<=(const Iterator<T> & other) const {
    return !((*this) > other); 
}

template <class T>
Iterator<T> & Iterator<T>::operator++() {
    if(rev)
        ptr--;
    else
        ptr++;
    return *this;
}

template <class T>
Iterator<T> & Iterator<T>::operator--() {
    if(rev)
        ptr++;
    else
        ptr--;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> temp(*this);
    if(rev)
        ptr--;
    else
        ptr++;
    return temp;
}

template <class T>
Iterator<T> Iterator<T>::operator--(int) {
    Iterator<T> temp(*this);
    if(rev)
        ptr++;
    else
        ptr--;
    return temp;
}

template <class T>
Iterator<T> & Iterator<T>::operator+=(int n) {
    if(rev)
        ptr -= n;
    else
        ptr += n;
    return *this;
}

template <class T>
Iterator<T> & Iterator<T>::operator-=(int n) {
    return operator+=(-n);
}

template <class T>
Iterator<T> Iterator<T>::operator+(int n) const {
    return Iterator(ptr + n, rev);
}

template <class T>
Iterator<T> operator+(long long n, const Iterator<T>& other) {
    Iterator<T> it = other;
    return (it += n);
}

template <class T>
Iterator<T> Iterator<T>::operator-(int n) const {
    return Iterator(ptr - n, rev);
}

template <class T>
long long Iterator<T>::operator-(const Iterator<T>& other) const {
    Iterator it = other;
    if( rev != it.rev)
        throw std::logic_error("Subtraction of differrent types of iterators!");
    int64_t n = 0;
    if(other == (*this))
        return n;
    return (ptr - other.ptr);
}

template <class T>
T & Iterator<T>::operator*() {
    return *ptr;
}

template <class T>
const T & Iterator<T>::operator*() const {
    return *ptr;
}

template <class T>
T & Iterator<T>::operator[](size_t n) {
    return ptr[n];
}

template <class T>
const T & Iterator<T>::operator[](size_t n) const {
    return ptr[n];
}


template<class T, class Alloc = allocator<T>>
class vector {
    Alloc alloc;
    T* ptr;
    size_t _capacity;
    size_t _size;
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;
    using iterator = Iterator<T>;


    vector();
    explicit vector(size_type count);
    vector(size_type count, const_reference defaultValue);
    vector(std::initializer_list<value_type> init);

    reference operator[](size_t n);
    const_reference operator[](size_t n) const;

    vector(const vector& other);

    vector( vector&& other) noexcept;

    vector& operator=(vector&& other) noexcept;

    void push_back(const_reference value);
    void push_back(value_type&& other);

    template<class... Args>
    T& emplace_back(Args&&... args) {
        if(_size == _capacity)
            reserve(2 * _capacity);
        alloc.construct((ptr + (_size++)), std::forward<Args>(args)...);
        return *(ptr + _size - 1);
    }

    void pop_back();
    bool empty() const;
    size_type size() const;
    size_type capacity() const;
    iterator begin() noexcept;
    iterator rbegin() noexcept;
    iterator end() noexcept;
    iterator rend() noexcept;
    void reserve(size_type count);
    void resize(size_type count);
    void resize(size_type count, const_reference defaultValue);
    void clear() noexcept;
};

template<class T, class Alloc>
vector<T, Alloc>::vector(){
    alloc = Alloc();
    _capacity = 4;
    ptr = alloc.allocate(_capacity);
    _size = 0;
}

template<class T, class Alloc>
vector<T, Alloc>::vector(size_type count) {
    if(count) 
        _capacity = 2 * count;
    else
        _capacity = 2;
    _size = count;
    ptr = alloc.allocate(_capacity);
    for(size_t i = 0; i < count; i++) {
        alloc.construct(ptr + i, value_type());
    }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(size_type count, const_reference defaultValue) {
    alloc = Alloc();
    if(count) 
        _capacity = 2 * count;
    else
        _capacity = 2;
    _size = count;
    ptr = alloc.allocate(_capacity);
    for(size_t i = 0; i < count; i++) {
        ptr[i] = defaultValue;
    }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(std::initializer_list<value_type> init) {
    alloc = Alloc();
    _size = init.size();
    _capacity = 2 * _size;
    ptr = alloc.allocate(_capacity);
    size_t i = 0;
    auto current = init.begin();
    const auto end = init.end();
    while (current != end)
        ptr[i++] = *current++;
}

template<class T, class Alloc>
vector<T, Alloc>::vector(const vector<T, Alloc>& other) {
    _size = other._size;
    _capacity = other._capacity;
    alloc = other.alloc;
    ptr = alloc.allocate(_capacity);
    for(size_t i = 0; i < other._size; ++i) {
        alloc.construct(ptr + i, *(other.ptr + i));
    }
}

template<class T, class Alloc>
vector<T, Alloc>::vector( vector<T, Alloc>&& other) noexcept : _size(std::move(other._size)), _capacity(std::move(other._capacity)), alloc(std::move(other.alloc)) {
    ptr = other.ptr;
    other.ptr = nullptr;
    other._size = 0;
}

template<class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(vector<T, Alloc>&& other) noexcept {
    if(this == &other)
        return (*this);
    for(size_t i = 0; i < _size; ++i) {
        alloc.destroy(ptr + i);
    }
    alloc.deallocate(ptr);
    _size = std::move(other._size);
    _capacity = other._capacity;
    alloc = std::move(other.alloc);
    ptr = other.ptr;
    other.ptr = nullptr;
    other._size = 0;
    return (*this);
}

template<class T, class Alloc>
T & vector<T, Alloc>::operator[](size_t n) {
    return ptr[n];
}

template<class T, class Alloc>
const T & vector<T, Alloc>::operator[](size_t n) const {
    return ptr[n];
}

template<class T, class Alloc>
void vector<T, Alloc>::push_back(const_reference value) {
    if(_size == _capacity) 
        reserve(2 *_capacity);
    ptr[_size++] = value; 
}

template<class T, class Alloc>
void vector<T, Alloc>::push_back(value_type&& other) {
    if(_size == _capacity)
        reserve(2 * _capacity);
    alloc.construct((ptr + (_size++)), std::forward<value_type>(other));
}

template<class T, class Alloc>
void vector<T, Alloc>::pop_back() {
    if(_size) {
        alloc.destroy(ptr + _size - 1);
        --_size;
    } else
        throw std::out_of_range("pop_back in empty vector");
}

template<class T, class Alloc>
bool vector<T, Alloc>::empty() const {
    return !_size;
}

template<class T, class Alloc>
size_t vector<T, Alloc>::size() const {
    return _size; 
}

template<class T, class Alloc>
size_t vector<T, Alloc>::capacity() const {
    return _capacity; 
}

template<class T, class Alloc>
void vector<T, Alloc>::clear() noexcept {
    for(size_t i = 0; i < _size; i++)
        alloc.destroy(ptr + i);
    _size = 0;
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::begin() noexcept {
    return iterator(ptr);
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::rbegin() noexcept {
    return iterator(ptr + _size - 1, true);
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::end() noexcept {
    return iterator(ptr + _size);
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::rend() noexcept {
    return iterator(ptr - 1, true);
}

template<class T, class Alloc>
void vector<T, Alloc>::resize(size_type count) {
    if(_size > count) 
        for(size_t i = count; i < _size; i++)
            alloc.destroy(ptr + i);
    else {
        if(count > _capacity)
            reserve(2 * count);
        for(size_t i = _size; i < count; i++)
            alloc.construct(ptr + i, value_type());
    }
    _size = count;
}

template<class T, class Alloc>
void vector<T, Alloc>::resize(size_type count, const_reference defaultValue) {
    if(_size > count) 
        for(size_t i = count; i < _size; i++)
            alloc.destroy(ptr + i);
    else {
        if(count > _capacity)
            reserve(2 * count);
        for(size_t i = _size; i < count; i++)
            ptr[i] = defaultValue;
    }
    _size = count;
}

template<class T, class Alloc>
void vector<T, Alloc>::reserve(size_type count) {
    if(count > _capacity) {
        T* _ptr= alloc.allocate(count);
        for(size_t i = 0; i < _size; i++) {
            _ptr[i] = ptr[i];
            alloc.destroy(ptr + i);
        }
        alloc.deallocate(ptr, _size);
        ptr = _ptr;
        _capacity = count;
    }
}