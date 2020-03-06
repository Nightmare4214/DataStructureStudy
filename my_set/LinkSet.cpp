#include "LinkSet.hpp"

template<typename T>
LinkSet<T>::LinkSet():first(new Node<T>()){}

template<typename T>
LinkSet<T>::~LinkSet() {
    while(this->first!= nullptr){
        Node<T>* p=this->first->next;
        delete this->first;
        this->first=p;
    }
}

template<typename T>
LinkSet<T>::LinkSet(const LinkSet &A) {
    this->first=new Node<T>();
    Node<T>* p,*q;
    p=first;
    q=A.first->next;
    while(q!=nullptr){
        p->next=new Node<T>(q->element);
        p=p->next;
        q=q->next;
    }
}
/**
 * 判断是否为空
 * @return 是否为空
 */
template<typename T>
bool LinkSet<T>::is_empty() const {
    return nullptr == first->next;
}
/**
 * 获得集合大小
 * @return 集合大小
 */
template<typename T>
int LinkSet<T>::set_size() const {
    Node<T>* p=first->next;
    int cnt=0;
    while(p!=nullptr){
        ++cnt;
        p=p->next;
    }
    return cnt;
}
/**
 * 求并集
 * @param A 集合
 */
template<typename T>
void LinkSet<T>::set_union(const LinkSet &A) {
    Node<T>* pre,*p,*q;
    pre=this->first;
    p=pre->next;
    q=A.first->next;
    while(p!=nullptr&&q!=nullptr){
        if(p->element<q->element){
            pre=p;
            p=p->next;
        }
        else if(p->element==q->element){
            pre=p;
            p=p->next;
            q=q->next;
        }
        else{
            pre->next=new Node<T>(q->element);
            pre->next->next=p;
            pre=pre->next;
            q=q->next;
        }
    }
    while(q!= nullptr){
        pre->next=new Node<T>(q->element);
        pre->next->next=p;
        pre=pre->next;
        q=q->next;
    }
}
/**
 * 交集
 * @param A 集合
 */
template<typename T>
void LinkSet<T>::set_intersection(const LinkSet &A) {
    Node<T>* pre,*p,*q;
    pre=this->first;
    p=pre->next;
    q=A.first->next;
    while(p!=nullptr&&q!=nullptr){
        if(p->element<q->element){
            pre->next=p->next;
            delete p;
            p=pre->next;
        }
        else if(p->element==q->element){
            pre=p;
            p=p->next;
            q=q->next;
        }
        else{
            q=q->next;
        }
    }
    while(p!=nullptr){
        pre->next=p->next;
        delete p;
        p=pre->next;
    }
}
/**
 * 差
 * @param A 集合
 */
template<typename T>
void LinkSet<T>::set_difference(const LinkSet &A) {
    Node<T>* pre,*p,*q;
    pre=this->first;
    p=pre->next;
    q=A.first->next;
    while(p!=nullptr&&q!=nullptr){
        if(p->element<q->element){
            pre=p;
            p=p->next;
        }
        else if(p->element==q->element){
            pre->next=p->next;
            delete p;
            p=pre->next;
            q=q->next;
        }
        else{
            q=q->next;
        }
    }
    while(p!=nullptr){
        pre->next=p->next;
        delete p;
        p=pre->next;
    }
}
/**
 * 赋值
 * @param A 集合
 * @return
 */
template<typename T>
void LinkSet<T>::set_assign(const LinkSet &A) {
    while(this->first->next!=nullptr){
        Node<T>* temp=this->first->next;
        this->first->next=temp->next;
        delete temp;
        temp=nullptr;
    }
    Node<T>* p,*q;
    p=this->first;
    q=A.first->next;
    while(q!=nullptr){
        p->next=new Node<T>(q->element);
        p=p->next;
        q=q->next;
    }
}
/**
 * 判断是否相等（set_size和每个元素都要相等）
 * @param A 集合
 * @return 是否相等
 */
template<typename T>
bool LinkSet<T>::set_equal(const LinkSet &A) const {
    Node<T>* p,*q;
    p=this->first->next;
    q=A.first->next;
    while(p!=nullptr&&q!=nullptr&&p->element==q->element){
        p=p->next;
        q=q->next;
    }
    return p== nullptr&&q== nullptr;
}
/**
 * 判断x是否在集合中
 * @param x 元素
 * @return true/false
 */
template<typename T>
bool LinkSet<T>::set_member(const T &x) const {
    Node<T>* p=this->first->next;
    while(p!= nullptr&&p->element<x){
        p=p->next;
    }
    return nullptr != p && x == p->element;
}
/**
 * 插入
 * @param x 数字
 * @return 是否插入成功
 */
template<typename T>
bool LinkSet<T>::set_insert(const T &x) {
    Node<T>* p,*q;
    p=this->first;
    q=p->next;
    while(q!=nullptr&&q->element<x){
        p=p->next;
        q=q->next;
    }
    if(nullptr != q && x == q->element){
        return false;
    }
    p->next=new Node<T>(x);
    p->next->next=q;
    return true;
}

template<typename T>
bool LinkSet<T>::set_delete(const T &x) {
    Node<T>* p,*q;
    p=this->first;
    q=p->next;
    while(q!=nullptr&&q->element<x){
        p=p->next;
        q=q->next;
    }
    if(q==nullptr||q->element!=x){
        return false;
    }
    p->next=q->next;
    delete q;
    q=nullptr;
    return true;
}

template<typename T>
void LinkSet<T>::print() const {
    Node<T>* p=this->first->next;
    bool flag=false;
    while(p!=nullptr){
        if(flag){
            std::cout<<' ';
        }
        else{
            flag=true;
        }
        std::cout<<p->element;
        p=p->next;
    }
}
/*
#include <iostream>
#include "my_set/LinkSet.cpp"
using namespace std;
int main() {
    LinkSet<int> A;
    for(int i=1;i<=3;++i){
        A.set_insert(i);
    }
    LinkSet<int> B;
    for(int i=3;i<=5;++i){
        B.set_insert(i);
    }
    A.print();
    cout<<endl;
    B.print();
    cout<<endl;
    LinkSet<int> C=A,D=A,E=A;
    C.set_union(B);
    C.print();
    cout<<endl;

    D.set_intersection(B);
    D.print();
    cout<<endl;

    E.set_difference(B);
    E.print();
    cout<<endl;

    cout<<A.set_member(1)<<endl;
    cout<<A.set_insert(6)<<endl;
    A.print();
    cout<<endl;
    cout<<A.set_delete(3)<<endl;
    A.print();
    cout<<endl;
    return 0;
}
 */