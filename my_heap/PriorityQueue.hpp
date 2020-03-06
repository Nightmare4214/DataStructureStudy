#pragma once
#include <iostream>
#include <cstring>
template<typename T>
class PriorityQueue{
private:
    T* heap;
    size_t max_size;
    size_t last;
    bool (*cmp)(const T&,const T&);
    void adjust(int cur);
public:
    PriorityQueue(const size_t& size,bool (*cmp)(const T&,const T&));
    ~PriorityQueue();
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue(const T& a,const size_t& size,bool (*cmp)(const T&,const T&));
    bool build(T a[],const size_t& size);
    bool insert(const T& x);
    bool pop();
    void heap_sort();
    void print()const;
};