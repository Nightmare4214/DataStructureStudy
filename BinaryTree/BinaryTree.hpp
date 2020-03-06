#pragma once
#include"TreeNode.hpp"
#include<vector>
#include<string>
template<typename T>
class BinaryTree {
private:
    TreeNode<T>* root;
    TreeNode<T>* create_tree();
    TreeNode<T>* create_tree(std::string& s);
    typedef typename std::vector<T>::iterator Iter;
    static TreeNode<T>* build_tree_with_pre_in_order(Iter pre_start,Iter pre_end,Iter in_start,Iter in_end);
    static TreeNode<T>* build_tree_with_in_post_order(Iter in_start, Iter in_end, Iter post_start, Iter post_end);
    static TreeNode<T>* build_tree_with_level_in_order(std::vector<T> level_order,
                                                       std::vector<T> in_order,
                                                       int in_start,
                                                       int in_end);
    void destroy(TreeNode<T>** rt);
    int get_depth(TreeNode<T>* rt)const;
    void pre_order_traversal(TreeNode<T>* rt)const;
    void in_order_traversal(TreeNode<T>* rt)const;
    void post_order_traversal(TreeNode<T>* rt)const;
    static bool is_full_binary_tree(TreeNode<T>* rt);
    static int kth_floor_Node(TreeNode<T>* rt,const size_t& k);
    static int min_depth(TreeNode<T>* rt);
    static void flatten(TreeNode<T> * rt);
    static bool judge_root(TreeNode<T>* left, TreeNode<T>* right);
    static bool is_symmetric(TreeNode<T> * rt);
    static bool is_complete_binary_tree(TreeNode<T>* rt);
public:
    static TreeNode<T>* cloneTree(const TreeNode<T>* rt);
    BinaryTree();
    BinaryTree(const TreeNode<T>* src_root_node);
    BinaryTree(const BinaryTree& src_tree);
    void clone_from(const BinaryTree& src);
    void clone_from(const TreeNode<T>* src);
    ~BinaryTree();
    void build_tree();
    void build_tree(const std::string& s);
    void build_tree_level();
    void build_tree_level(const std::string& s);
    std::string serialize()const;
    static TreeNode<T>* build_tree_with_pre_in_order(std::vector<T> pre_order, std::vector<T> in_order);
    static TreeNode<T>* build_tree_with_in_post_order(std::vector<T> in_order, std::vector<T> post_order);
    static TreeNode<T>* build_tree_with_level_in_order(std::vector<T> level_order, std::vector<T> in_order);
    void build_with_pre_in_order(std::vector<T> pre_order, std::vector<T> in_order);
    void build_with_in_post_order(std::vector<T> in_order, std::vector<T> post_order);
    void build_with_level_post_order(std::vector<T> level_order, std::vector<T> in_order);
    void destroy();
    void pre_order_traversal()const;
    void pre_order_traversal_non_recursive()const;
    void in_order_traversal()const;
    void in_order_traversal_non_recursive()const;
    void post_order_traversal()const;
    void post_order_traversal_non_recursive()const;
    void post_order_traversal_non_recursive2()const;
    void post_order_traversal_non_recursive3()const;
    void post_order_traversal_non_recursive4()const;
    void level_order_traversal()const;
    TreeNode<T>* find_one(const T& target)const;
    static TreeNode<T>* lowest_common_ancestor(TreeNode<T>* rt, TreeNode<T>* A, TreeNode<T>* B);
    TreeNode<T>* lowest_common_ancestor(TreeNode<T>* A, TreeNode<T>* B)const;
    int get_depth()const;
    bool is_full_binary_tree()const;
    int kth_floor_Node(const size_t& k)const;
    int min_depth()const;
    void flatten();
    TreeNode<T>* clone()const;
    bool is_symmetric()const;
    bool is_complete_binary_tree()const;
};