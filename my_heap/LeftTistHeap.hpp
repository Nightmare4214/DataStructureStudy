#pragma once
#include <iostream>
#include <queue>
template<typename T>
class LeftTistHeapNode{
public:
    int left,right,dist;
    T val;
    LeftTistHeapNode():left(0),right(0),dist(0){}
    explicit LeftTistHeapNode(const T& x):val(x),left(0),right(0),dist(-1){}
};
template<typename T>
class LeftTistHeap{
private:
    LeftTistHeapNode<T>* heap;
    size_t* parent;
    size_t max_size;
    size_t find_parent(const size_t& x)const;
public:
    explicit LeftTistHeap(const size_t& size);
    bool build(T a[],int size);
    size_t merge_heap(size_t x, size_t y);
    size_t pop(const size_t& x);
};
