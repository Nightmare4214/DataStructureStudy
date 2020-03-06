#pragma once
#include <string>
#include <utility>
class ExpressionTreeNode {
public:
    std::string data;
    ExpressionTreeNode* left, * right;
    ExpressionTreeNode() : left(nullptr), right(nullptr) {}
    explicit ExpressionTreeNode(std::string  data) : data(std::move(data)), left(nullptr), right(nullptr) {}
    ExpressionTreeNode(ExpressionTreeNode* left, ExpressionTreeNode* right, std::string  data): data(std::move(data)), left(left), right(right) {}
    ExpressionTreeNode(ExpressionTreeNode* left, ExpressionTreeNode* right, const char& data) : data(std::string(1, data)), left(left), right(right) {}
};