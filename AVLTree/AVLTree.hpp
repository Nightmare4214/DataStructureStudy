#pragma once

#include "AVLTreeNode.hpp"

template<typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root;
    size_t getHeight(AVLTreeNode<T>* tree) const;
    void updateHeight(AVLTreeNode<T> * rt);
    AVLTreeNode<T>* LeftLeftRotation(AVLTreeNode<T>* rt);
    AVLTreeNode<T>* RightRightRotation(AVLTreeNode<T>* rt);
    AVLTreeNode<T>* LeftRightRotation(AVLTreeNode<T>* rt);
    AVLTreeNode<T>* RightLeftRotation(AVLTreeNode<T>* rt);
    AVLTreeNode<T>* insert(AVLTreeNode<T>* rt, const T &value);
    AVLTreeNode<T>* getMax(AVLTreeNode<T>* rt);
    AVLTreeNode<T>* getMin(AVLTreeNode<T>* rt);
    AVLTreeNode<T>* remove(AVLTreeNode<T>* rt, const T &value);
    void destroy(AVLTreeNode<T>* rt);
    void preOrder(AVLTreeNode<T>* rt) const;
    void inOrder(AVLTreeNode<T>* rt) const;
    void postOrder(AVLTreeNode<T>* rt) const;
    void layerOrder(AVLTreeNode<T>* rt) const;
    AVLTreeNode<T>* search(AVLTreeNode<T>* rt, const T &value) const;
public:
    AVLTree();
    ~AVLTree();
    void destroy();
    size_t getHeight() const;
    void insert(const T &value);
    void remove(const T &value);
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void layerOrder() const;
    AVLTreeNode<T>* search(const T &value) const;
};
