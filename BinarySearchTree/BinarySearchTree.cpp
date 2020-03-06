#include "BinarySearchTree.hpp"
#include <iostream>
/**
 * 往以rt为根的树插入节点
 * @param rt 根
 * @param value 值
 */
template<typename T>
void BST<T>::insert(Node<T> *rt, const T &value) {
    Node<T>* parent = nullptr;
    while (rt) {
        parent = rt;
        //这个值已经有了
        if (rt->value == value){
            return;
        }
        if (value < rt->value){
            rt = rt->left;
        }
        else {
            rt = rt->right;
        }
    }
    rt = new Node<T>(value);
    rt->parent = parent;
    if (nullptr == parent){
        root = rt;
    }
    else if (value < parent->value){
        parent->left = rt;
    }
    else {
        parent->right = rt;
    }
}
/**
 * 查找rt为根的最小值
 * @param rt 根
 * @return 最小值的节点
 */
template<typename T>
Node<T> *BST<T>::getMin(Node<T> *rt) const {
    if (nullptr == rt){
        return nullptr;
    }
    while (rt->left){
        rt = rt->left;
    }
    return rt;
}
/**
 * 查找rt为根的最大值
 * @param rt 根
 * @return 最大值的节点
 */
template<typename T>
Node<T> *BST<T>::getMax(Node<T> *rt) const {
    if (nullptr == rt){
        return nullptr;
    }
    while (rt->right){
        rt = rt->right;
    }
    return rt;
}
/**
 * 前序遍历
 * @param rt 根节点
 */
template<typename T>
void BST<T>::preOrder(Node<T> *rt) const {
    if(nullptr == rt){
        return;
    }
    std::cout << rt->value << ' ';
    if(rt->left != nullptr){
        preOrder(rt->left);
    }
    if(rt->right != nullptr){
        preOrder(rt->right);
    }
}
/**
 * 中序遍历
 * @param rt 根节点
 */
template<typename T>
void BST<T>::inOrder(Node<T> *rt) const {
    if(nullptr == rt){
        return;
    }
    if(rt->left != nullptr){
        inOrder(rt->left);
    }
    std::cout << rt->value << ' ';
    if(rt->right != nullptr){
        inOrder(rt->right);
    }
}
/**
 * 后序遍历
 * @param rt 根节点
 */
template<typename T>
void BST<T>::postOrder(Node<T> *rt) const {
    if(nullptr == rt){
        return;
    }
    if(rt->left != nullptr){
        postOrder(rt->left);
    }
    if(rt->right != nullptr){
        postOrder(rt->right);
    }
    std::cout << rt->value << ' ';
}
/**
 * 销毁以rt为根节点的二叉树
 * @param rt 根
 */
template<typename T>
void BST<T>::destroy(Node<T> *rt) {
    if(nullptr == rt){
        return;
    }
    if(rt->left!=nullptr){
        destroy(rt->left);
    }
    if(rt->right!=nullptr){
        destroy(rt->right);
    }
    delete rt;
}

template<typename T>
BST<T>::BST():root(nullptr) {

}

template<typename T>
BST<T>::~BST() {
    destroy(root);
}
/**
 * 前序遍历
 */
template<typename T>
void BST<T>::preOrder() const {
    preOrder(root);
    std::cout<<std::endl;
}
/**
 * 中序遍历
 */
template<typename T>
void BST<T>::inOrder() const {
    inOrder(root);
    std::cout<<std::endl;
}
/**
 * 后序遍历
 */
template<typename T>
void BST<T>::postOrder() const {
    postOrder(root);
    std::cout<<std::endl;
}
/**
 * 插入值为value的节点
 * @param value 值
 */
template<typename T>
void BST<T>::insert(const T &value) {
    insert(root, value);
}
/**
 * 返回最小值的节点
 * @return 节点
 */
template<typename T>
Node<T> *BST<T>::getMin() const {
    return getMin(root);
}
/**
 * 返回最大值的节点
 * @return 节点
 */
template<typename T>
Node<T> *BST<T>::getMax() const {
    return getMax(root);
}
/**
 * 返回value的节点
 * @param value 值
 * @return 节点
 */
template<typename T>
Node<T> *BST<T>::search(const T &value) const {
    Node<T>* rt = root;
    while (rt&&rt->value != value) {
        if (value < rt->value){
            rt = rt->left;
        }
        else {
            rt = rt->right;
        }
    }
    return rt;
}
/**
 * 返回node的值在树中的位置
 * @param node 节点
 * @return 位置
 */
template<typename T>
Node<T> *BST<T>::search(const Node<T> *node) const {
    return search(node->value);
}
/**
 * 获得rt的后继
 * @param rt 根
 * @return 后继
 */
template<typename T>
Node<T> *BST<T>::getSuccessor(const Node<T> *rt) const {
    if (nullptr == rt){
        return nullptr;
    }
    if (rt->right){
        return getMin(rt->right);
    }
    Node<T>* parent = rt->parent;
    while (parent&&parent->right != rt) {
        rt = parent;
        parent = parent->parent;
    }
    return parent;
}
/**
 * 获得rt的前驱
 * @param rt 根
 * @return 前驱
 */
template<typename T>
Node<T> *BST<T>::getPredecessor(const Node<T> *rt) const {
    if (nullptr == rt){
        return nullptr;
    }
    if (rt->left){
        getMax(rt->left);
    }
    Node<T>* parent = rt->parent;
    while (parent&&parent->left != rt) {
        rt = parent;
        parent = parent->parent;
    }
    return parent;
}
/**
 * 删除值为value的节点
 * @param value 值
 */
template<typename T>
void BST<T>::remove(const T &value) {
    Node<T>* z = search(value);
    if (z == nullptr)return;
    Node<T>*parent = z->parent, *del = z;
    //只有右子树
    if (z->left == nullptr) {
        //删除节点为根节点
        if (z == root) {
            root = z->right;
            if (root != nullptr)root->parent = nullptr;
        }
        else if (z == parent->left){
            parent->left = z->right;
        }
        else{
            parent->right = z->right;
        }
    }
    else if (z->right == nullptr) { //只有左子树
        //删除节点为根节点
        if (z == root) {
            root = z->right;
            if (root != nullptr)root->parent = nullptr;
        }
        else if (z == parent->left){
            parent->left = z->left;
        }
        else {
            parent->right = z->left;
        }
    }
    else {
        //找到右子树的的最小值，也就是中序遍历的后继结点
        Node<T>* t = getMin(z->right), *parent = t->parent;
        del = t;
        z->value = t->value;
        if (parent->left == t){
            parent->left = t->right;
        }
        else {
            parent->right = t->right;
        }
    }
    delete del;
}
/*
#include <iostream>
#include "BinarySearchTree/BinarySearchTree.cpp"
using namespace std;
int main() {
    BST<int> test;
    test.insert(50);
    test.preOrder();
    test.inOrder();
    test.postOrder();
    cout << test.getMin()->value << endl;
    cout << test.getMax()->value << endl;
    test.remove(50);
    test.preOrder();
    test.inOrder();
    test.insert(50);
    test.insert(30);
    test.insert(20);
    test.insert(40);
    test.insert(35);
    test.insert(32);
    test.insert(80);
    test.insert(90);
    test.insert(85);
    test.insert(88);
    test.preOrder();
    test.inOrder();
    return 0;
}
 */