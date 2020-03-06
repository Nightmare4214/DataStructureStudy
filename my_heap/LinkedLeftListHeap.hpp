#pragma once

#include <iostream>
#include <queue>
template<typename T>
class LinkedNode{
public:
    int dist;
    T val;
    LinkedNode<T>* left,*right;
    LinkedNode():dist(0),left(nullptr),right(nullptr){}
    explicit LinkedNode(const T& x):val(x),dist(0),left(nullptr),right(nullptr){}
};
template<typename T>
class LinkedLeftListHeap{
private:
    LinkedNode<T>* root;
    void destroy(LinkedNode<T>** rt);
    LinkedNode<T>* _merge(LinkedNode<T>* x,LinkedNode<T>* y);
public:
    LinkedLeftListHeap();
    ~LinkedLeftListHeap();
    void merge(LinkedNode<T>* x,LinkedNode<T>* y);
    void insert(const T& x);
    T get_top()const;
    T pop();
    void build(T a[],size_t size);
};