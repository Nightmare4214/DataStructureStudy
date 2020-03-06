#pragma once
template<typename T>
class TreeNode {
public:
    T data;
    TreeNode<T>* left, * right;
    TreeNode() :left(nullptr), right(nullptr) {}
    explicit TreeNode(const T& data) :data(data), left(nullptr), right(nullptr) {}
};