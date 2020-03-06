#include "LeftTistHeap.hpp"

template<typename T>
size_t LeftTistHeap<T>::find_parent(const size_t &x) const {
    size_t p=x;
    while(p!=parent[p]){
        p=parent[p];
    }
    size_t adjust=x;
    while(adjust!=parent[adjust]){
        size_t temp=parent[adjust];
        parent[adjust]=p;
        adjust=temp;
    }
    return parent;
}

template<typename T>
LeftTistHeap<T>::LeftTistHeap(const size_t &size):max_size(size) {
    heap=new LeftTistHeapNode<T>[size];
    parent=new size_t[size];
    for(size_t i=0;i<size;++i){
        parent[i]=i;
    }
    heap[0].dist=-1;
}
/**
 * 赋值
 * @param a
 * @param size
 * @return
 */
template<typename T>
bool LeftTistHeap<T>::build(T *a, int size) {
    if(size<=0||size>max_size+1){
        return false;
    }
    std::queue<size_t> q;
    for(size_t i=0;i<size;++i){
        heap[i+1]=LeftTistHeapNode<T>(a[i]);
        q.push(i+1);
    }
    for(size_t i=1;i<max_size;++i){
        parent[i]=i;
    }
    while(!q.empty()){
        size_t x=q.front();
        q.pop();
        if(q.empty()){
            break;
        }
        size_t y=q.front();
        q.pop();
        x= merge_heap(x, y);
        if(x<max_size){
            q.push(x);
        }
    }
    return true;
}

/**
 * 合并
 * @param x 左偏树1
 * @param y 左偏树2
 * @return 堆顶
 */
template<typename T>
size_t LeftTistHeap<T>::merge_heap(size_t x, size_t y) {
    if(x<=0||x>max_size||y<=0||y>max_size) {
        return -1;
    }
    if(x==0||y==0){
        return x+y;
    }
    if(heap[x].val>heap[y].val){
        std::swap(x,y);
    }
    heap[x].right= merge_heap(heap[x].right, y);
    parent[heap[x].right]=x;
    if(heap[heap[x].left].dist<heap[heap[x].right].dist){
        std::swap(heap[x].left,heap[x].right);
    }
    heap[x].dist=heap[x].right+1;
    return x;
}
/**
 * 删除元素所在堆顶的最小元素
 * @param y 元素
 * @return 删除后的堆顶，失败返回max_size
 */
template<typename T>
size_t LeftTistHeap<T>::pop(const size_t &y) {
    if(y<=0||y>max_size){
        return max_size;
    }
    size_t x=find_parent(y);
    size_t left=heap[x].left;
    size_t right=heap[x].right;
    parent[left]=left;
    parent[right]=right;
    parent[x]= merge_heap(left, right);
    size_t top=parent[x];
    return top;
}