#pragma once
#include <iostream>
template<typename T>
class Node{
public:
    T element;
    Node<T>* next;
    Node():next(nullptr){}
    Node(const T& element):element(element),next(nullptr){}
};
template<typename T>
class LinkSet{
private:
    Node<T>* first;
public:
    LinkSet();
    ~LinkSet();
    LinkSet(const LinkSet& A);
    bool is_empty()const;
    int set_size()const;
    void set_union(const LinkSet& A);
    void set_intersection(const LinkSet& A);
    void set_difference(const LinkSet& A);
    void set_assign(const LinkSet& A);
    bool set_equal(const LinkSet& A)const;
    bool set_member(const T& x)const;
    bool set_insert(const T& x);
    bool set_delete(const T& x);
    void print()const;
};