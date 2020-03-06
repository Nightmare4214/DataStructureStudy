#include "BinarySearchTreeNode.hpp"
template<typename T>
class BST {
private:
    Node<T>* root;
    void insert(Node<T> *rt, const T &value);
    Node<T>* getMin(Node<T>* rt)const;
    Node<T>* getMax(Node<T>* rt)const;
    void preOrder(Node<T> * rt)const;
    void inOrder(Node<T>* root)const;
    void postOrder(Node<T>* root)const;
    void destroy(Node<T>* rt);
public:
    BST();
    ~BST();
    void preOrder()const;
    void inOrder()const;
    void postOrder()const;
    void insert(const T &value);
    Node<T>* getMin()const;
    Node<T>* getMax()const;
    Node<T>* search(const T &value)const;
    Node<T>* search(const Node<T>* node)const;
    Node<T>* getSuccessor(const Node<T>* rt)const;
    Node<T>* getPredecessor(const Node<T>* rt)const;
    void remove(const T &value);
};


