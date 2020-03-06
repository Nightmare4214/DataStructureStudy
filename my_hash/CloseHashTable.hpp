#pragma once
#include <iostream>
#include <cstring>
template<typename T>
class CloseHashTable{
private:
    size_t size;
    size_t (*hash)(const T&);
    //状态，0表示空，1表示被占用，2表示被占用但是删除了
    size_t* state;
    T* table;
    size_t hash_prob(int i)const;
public:
    CloseHashTable(const size_t& size,size_t (*hash)(const T&));
    size_t find_match(const T& x)const;
    size_t next_space(const T& x)const;
    bool member(const T& x)const;
    bool insert(const T& x);
    bool remove(const T& x);
};