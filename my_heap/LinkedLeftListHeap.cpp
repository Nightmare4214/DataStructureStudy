#include "LinkedLeftListHeap.hpp"
/**
 * 销毁
 * @param rt 根结点
 */
template<typename T>
void LinkedLeftListHeap<T>::destroy(LinkedNode<T> **rt) {
    if(nullptr == *rt){
        return;
    }
    if(nullptr != (*rt)->left){
        destroy((*rt)->left);
    }
    if(nullptr != (*rt)->right){
        destroy((*rt)->right);
    }
    delete *rt;
    *rt= nullptr;
}
template<typename T>
LinkedNode<T> *LinkedLeftListHeap<T>::_merge(LinkedNode<T> *x, LinkedNode<T> *y) {
    if(nullptr == x){
        return y;
    }
    if(nullptr == y){
        return x;
    }
    if(x->val>y->val){
        swap(x,y);
    }
    x->right=merge(x->right,y);
    if(nullptr == x->left){
        x->left=x->right;
        x->right= nullptr;
        x->dist=0;
    }
    else{
        if(x->right!=nullptr&&x->left->dist<x->right->dist){
            swap(x->left,x->right);
        }
        x->dist=x->right+1;
    }
    return x;
}

template<typename T>
LinkedLeftListHeap<T>::LinkedLeftListHeap():root(nullptr) {
}

template<typename T>
LinkedLeftListHeap<T>::~LinkedLeftListHeap() {
    if(nullptr != this->root){
        destroy(&(this->root));
        this->root= nullptr;
    }
}

template<typename T>
void LinkedLeftListHeap<T>::merge(LinkedNode<T> *x, LinkedNode<T> *y) {
    _merge(x,y);
}

template<typename T>
void LinkedLeftListHeap<T>::insert(const T &x) {
    auto* p=new LinkedNode<T>(x);
    this->root=_merge(this,p);
}

template<typename T>
T LinkedLeftListHeap<T>::get_top() const {
    return this->root->val;
}

template<typename T>
T LinkedLeftListHeap<T>::pop() {
    auto* p=this->root;
    assert(nullptr != p);
    auto* left=p->left;
    auto* right=p->right;
    T temp=p->v;
    delete p;
    p=nullptr;
    this->root=_merge(left,right);
    return temp;
}

template<typename T>
void LinkedLeftListHeap<T>::build(T *a, size_t size) {
    std::queue<LinkedNode<T>*> q;
    for(size_t i=0;i<size;++i){
        q.push(new LinkedNode<T>(a[i]));
    }
    while(!q.empty()){
        LinkedNode<T>* p=q.front();
        if(q.empty()){
            this->root=p;
            break;
        }
        LinkedNode<T>* r=q.front();
        q.pop();
        q.push(_merge(p,r));
    }
}