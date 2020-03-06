#include "CloseHashTable.hpp"

template<typename T>
CloseHashTable<T>::CloseHashTable(const size_t &size, size_t (*hash)(const T &)):size(size),hash(hash) {
    state=new size_t[size]{};
    table=new T[size];
}
/**
 * 探测函数
 * @param i
 * @return 间距
 */
template<typename T>
size_t CloseHashTable<T>::hash_prob(int i) const {
    return i;
}
/**
 * 查找
 * @param x 元素
 * @return 返回位置，不存在返回长度
 */
template<typename T>
size_t CloseHashTable<T>::find_match(const T &x) const {
    size_t index=hash(x);
    for(size_t i=0;i<size;++i){
        size_t k=(index+hash_prob(i))%size;
        //这个位置是空的
        if(state[k]==0){
            return size;
        }
        else if(state[k]==1&&table[k]==x){
            return k;
        }
    }
    return size;
}
/**
 * 下一个空着的位置
 * @param x 元素
 * @return 空着的位置，满了返回size
 */
template<typename T>
size_t CloseHashTable<T>::next_space(const T &x) const {
    size_t index=hash(x);
    for(size_t i=0;i<size;++i){
        size_t k=(index+hash_prob(i))%size;
        //这个位置是空的
        if(state[k]==0){
            return k;
        }
        else if(state[k]==1&&table[k]==x){
            return size;
        }
    }
    return size;
}
/**
 * 查找
 * @param x 元素
 * @return 是否存在
 */
template<typename T>
bool CloseHashTable<T>::member(const T &x) const {
    size_t result=find_match(x);
    return result<size&&table[result]==x;
}

template<typename T>
bool CloseHashTable<T>::insert(const T &x) {
    size_t result=next_space(x);
    if(result>=size||table[result]==x){
        return false;
    }
    table[result]=x;
    state[result]=1;
    return true;
}

template<typename T>
bool CloseHashTable<T>::remove(const T &x) {
    size_t result=find_match(x);
    if(result>=size||table[result]!=x){
        return false;
    }
    state[result]=2;
    return true;
}