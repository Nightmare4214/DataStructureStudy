#pragma once
#include "ExpressionTreeNode.hpp"
class ExpressionTree {
private:
    ExpressionTreeNode* root;
    static int level(const char&);
    static int cmp(const char&, const char&);
    static bool is_operator(const char&);
    static void destroy(ExpressionTreeNode**);
    bool should_print_parenthesis(ExpressionTreeNode*, bool)const;
    void get_expression(ExpressionTreeNode*, std::string&)const;
    double getValue(ExpressionTreeNode*)const;
public:
    ExpressionTree() :root(nullptr) {};
    void destroy();
    ~ExpressionTree();
    void build_by_infix_expression(const std::string&);
    void build_by_rpn(const std::string&);
    void build_by_pn(const std::string&);
    std::string get_expression()const;
    std::string get_rpn()const;
    std::string get_pn()const;
    double getValue()const;
};