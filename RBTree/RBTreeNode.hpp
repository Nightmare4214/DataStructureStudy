#pragma once
enum COLOR { RED = 0, BLACK = 1 };
template<typename KEY, typename VALUE>
class RBTreeNode {
public:
    COLOR color;
    KEY key;
    VALUE value;
    RBTreeNode<KEY, VALUE>* parent;
    RBTreeNode<KEY, VALUE>* left;
    RBTreeNode<KEY, VALUE>* right;
    RBTreeNode() :color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
    RBTreeNode(const KEY& key, const VALUE& value, const COLOR& color = RED) :
            color(color), key(key), value(value), parent(nullptr), left(nullptr), right(nullptr) {}
};