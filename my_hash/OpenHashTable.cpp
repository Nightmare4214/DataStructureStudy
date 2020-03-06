#include "OpenHashTable.hpp"

template<typename T>
OpenHashTable<T>::OpenHashTable(size_t n_buckets, size_t (*hash)(const T&)):size(n_buckets),hash(hash) {
    bucket.reserve(n_buckets);
}
/**
 * 判断元素是否存在
 * @param x 元素
 * @return 是否存在
 */
template<typename T>
bool OpenHashTable<T>::member(const T &x) const {
    size_t index=hash(x)%this->size;
    for(size_t i=0;i<this->bucket[index].size();++i){
        if(x == this->bucket[index][i]){
            return true;
        }
    }
    return false;
}
/**
 * 插入
 * @param x 元素
 * @return 插入是否成功
 */
template<typename T>
bool OpenHashTable<T>::insert(const T &x) {
    size_t index=hash(x)%this->size;
    for(size_t i=0;i<this->bucket[index].size();++i){
        if(x == this->bucket[index][i]){
            return false;
        }
    }
    this->bucket[index].push_back(x);
    return true;
}
/**
 * 删除
 * @param x 元素
 * @return 删除是否成功
 */
template<typename T>
bool OpenHashTable<T>::remove(const T &x) {
    size_t index=hash(x)%this->size;
    for(auto* it=this->bucket[index].begin();it!=this->bucket[index].end();++it){
        if(*it==x){
            this->bucket[index].erase(it);
            return true;
        }
    }
    return false;
}