#include "PriorityQueue.hpp"
/**
 * 向下调整堆
 * @param cur 调整位置
 */
template<typename T>
void PriorityQueue<T>::adjust(int cur) {
    T temp=heap[cur];
    int child=cur<<1|1;
    while(child<last){
        if(child+1<last&&cmp(heap[child+1],heap[child])){
            ++child;
        }
        if(cmp(heap[child],temp)){
            heap[cur]=heap[child];
            cur=child;
            child=child*2+1;
        }
        else{
            break;
        }
    }
    heap[cur]=temp;
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const size_t &size,bool (*cmp)(const T&,const T&)):max_size(size),last(0),cmp(cmp) {
    heap=new T[size];
}

template<typename T>
PriorityQueue<T>::~PriorityQueue() {
    delete[] heap;
    heap=nullptr;
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue &other):max_size(other.max_size),last(other.last),cmp(other.cmp) {
    heap=new T[this->max_size];
    memcpy(heap,other.heap,sizeof(T)*this->max_size);
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const T &a, const size_t &size, bool (*cmp)(const T &, const T &)):max_size(size),last(size),cmp(cmp) {
    memcpy(heap,a,sizeof(T)*size);
    last=size;
    int cur=(last-1)/2;
    while(cur>=0){
        adjust(cur);
        --cur;
    }
}

/**
 * 插入
 * @param x 元素
 * @return 是否插入成功
 */
template<typename T>
bool PriorityQueue<T>::insert(const T &x) {
    if(last==max_size){
        return false;
    }
    int child=last;
    ++last;
    int parent=(child-1)>>1;
    T temp=heap[child];
    while(parent>=0){
        if(!cmp(heap[child],heap[parent])){
            heap[child]=heap[parent];
            child=parent;
            parent>>=1;
        }
        else{
            break;
        }
    }
    heap[child]=temp;
    return true;
}
/**
 * 弹出堆顶
 * @tparam T
 * @return
 */
template<typename T>
bool PriorityQueue<T>::pop() {
    if(last==0){
        return false;
    }
    --last;
    swap(heap[0],heap[last]);
    adjust(0);
    return true;
}
/**
 * 赋值
 * @param a 数组
 * @param size 大小
 * @return 调整成功
 */
template<typename T>
bool PriorityQueue<T>::build(T* a, const size_t& size) {
    if(size>max_size){
        return false;
    }
    memcpy(heap,a,sizeof(T)*size);
    last=size;
    int cur=last/2-1;
    while(cur>=0){
        adjust(cur);
        --cur;
    }
    return true;
}
/**
 * 堆排序
 * @tparam T
 */
template<typename T>
void PriorityQueue<T>::heap_sort() {
    int cur=last/2-1;
    while(cur>=0){
        adjust(cur);
        --cur;
    }
    for(int i=last-1;i>0;--i){
        swap(heap[i],heap[0]);
        adjust(0);
    }
}

template<typename T>
void PriorityQueue<T>::print() const {
    for(size_t i=0;i<last;++i){
        if(i>0){
            std::cout<<' ';
        }
        std::cout<<heap[i];
    }
}