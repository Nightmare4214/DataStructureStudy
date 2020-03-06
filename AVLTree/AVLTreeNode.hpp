#pragma once

#include <iostream>
template <typename T>
class AVLTreeNode{
public:
    T value;
    size_t height;
    AVLTreeNode* left,*right;
    AVLTreeNode():height(1),left(nullptr),right(nullptr){}
    explicit AVLTreeNode(const T& value):value(value),height(1),left(nullptr),right(nullptr){}
    explicit AVLTreeNode(T&& value):value(value),height(1),left(nullptr),right(nullptr){}
};