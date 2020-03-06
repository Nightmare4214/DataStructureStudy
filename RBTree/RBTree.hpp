#pragma once

#include "RBTreeNode.hpp"
template<typename KEY, typename VALUE>
class RBTree {
private:
    RBTreeNode<KEY, VALUE>* root;
    RBTreeNode<KEY, VALUE>* find(const KEY& key)const;
    RBTreeNode<KEY, VALUE>* insert_return(const KEY& key, const VALUE& value);
    void insert_fix(RBTreeNode<KEY, VALUE>* fix_node);
    void left_rotate(RBTreeNode<KEY, VALUE>* rotate_node);
    void right_rotate(RBTreeNode<KEY, VALUE>* rotate_node);
    RBTreeNode<KEY, VALUE>* in_order_predecessor(RBTreeNode<KEY, VALUE>* rt)const;
    RBTreeNode<KEY, VALUE>* in_order_successor(RBTreeNode<KEY, VALUE>* rt)const;
    void delete_fix(RBTreeNode<KEY, VALUE>* fix_node);
    void pre_order_traversal(RBTreeNode<KEY, VALUE>* rt)const;
    void in_order_traversal(RBTreeNode<KEY, VALUE>* rt)const;
    void post_order_traversal(RBTreeNode<KEY, VALUE>* rt)const;
    void level_order_traversal(RBTreeNode<KEY, VALUE>* rt)const;
    void destroy(RBTreeNode<KEY, VALUE>*& rt);
    bool check(RBTreeNode<KEY, VALUE>* rt, int& black_cnt)const;
public:
    RBTree();
    ~RBTree();
    void destroy();
    bool is_empty()const;
    void insert(const KEY& key, const VALUE& value);
    void remove(const KEY& key);
    void pre_order_traversal()const;
    void in_order_traversal()const;
    void post_order_traversal()const;
    void level_order_traversal()const;
    bool check()const;
    VALUE& operator[](const KEY& key);
};