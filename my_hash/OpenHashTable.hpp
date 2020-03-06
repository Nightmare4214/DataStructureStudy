#pragma once
#include <iostream>
#include <cstring>
#include <vector>
template<typename T>
class OpenHashTable{
private:
    size_t size;
    size_t (*hash)(const T& x);
    std::vector<std::vector<T> > bucket;
public:
    OpenHashTable(size_t n_buckets,size_t (*hash)(const T& x));
    bool member(const T& x)const;
    bool insert(const T& x);
    bool remove(const T& x);
};