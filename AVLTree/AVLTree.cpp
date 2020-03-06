#include "AVLTree.hpp"
#include <queue>
/**
 * 获得以tree为根节点的树的高度
 * @param tree 根节点
 * @return 根节点高度
 */
template<typename T>
size_t AVLTree<T>::getHeight(AVLTreeNode<T> *tree) const {
    if(nullptr==tree){
        return 0;
    }
    return tree->height;
}
/**
 * 更新以rt为根节点的树的高度
 * @param rt 根节点
 */
template<typename T>
void AVLTree<T>::updateHeight(AVLTreeNode<T> *rt) {
    if(nullptr==rt){
        return;
    }
    rt->height=std::max(getHeight(rt->left),getHeight(rt->right))+1;
}
/**
 * 对以rt根节点的树进行右旋(LL旋转)
 * @param rt 要旋转的树的根节点
 * @return 旋转后的根节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::LeftLeftRotation(AVLTreeNode<T> *rt) {
    if(nullptr==rt){
        return nullptr;
    }
    AVLTreeNode<T>* result=rt->left;
    rt->left=result->right;
    result->right=rt;
    updateHeight(rt);
    updateHeight(result);
    return result;
}
/**
 * 对以rt根节点的树进行左旋(RR旋转)
 * @param rt 要旋转的树的根节点
 * @return 旋转后的根节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::RightRightRotation(AVLTreeNode<T> *rt) {
    if(nullptr==rt){
        return nullptr;
    }
    AVLTreeNode<T>* result=rt->right;
    rt->right=result->left;
    result->left=rt;
    updateHeight(rt);
    updateHeight(result);
    return result;
}
/**
 * 对以rt根节点的树的进行LR旋转
 * 先对rt的左子树做左旋(RR旋转)，然后对rt进行右旋(LL旋转)
 * @param rt 要旋转的树的根节点
 * @return 旋转后的根节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::LeftRightRotation(AVLTreeNode<T> *rt) {
    if(nullptr==rt){
        return nullptr;
    }
    rt->left=RightRightRotation(rt->left);
    return LeftLeftRotation(rt);
}
/**
 * 对以rt根节点的树的进行RL旋转
 * 先对rt的右子树做右旋(LL旋转)，然后对rt进行左旋(RR旋转)
 * @param rt 要旋转的树的根节点
 * @return 旋转后的根节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::RightLeftRotation(AVLTreeNode<T> *rt) {
    if(nullptr==rt){
        return nullptr;
    }
    rt->right = LeftLeftRotation(rt->right);
    return RightRightRotation(rt);
}
/**
 * 对以rt为根节点的树插入值为value的节点
 * @param rt 要插入的树
 * @param value 要插入的值
 * @return 插入节点后的树
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::insert(AVLTreeNode<T> *rt, const T &value) {
    //空树
    if(nullptr==rt){
        return new AVLTreeNode<T>(value);
    }
    else if(value<rt->value){  //插左子树上
        rt->left=insert(rt->left,value);
        //左子树比右子树高2,失衡了
        if(getHeight(rt->left)>=getHeight(rt->right)+2){
            //插入在左子树的左子树上,说明要LL旋转
            if(value<rt->left->value){
                rt=LeftLeftRotation(rt);
            }
            else{ //插入在左子树的右子树上,说明要LR旋转
                rt=LeftRightRotation(rt);
            }
        }
    }
    else if(value>rt->value){ //插右子树上
        rt->right=insert(rt->right,value);
        //右子树比左子树高2,失衡了
        if(getHeight(rt->right)>=getHeight(rt->left)+2){
            //插入在右子树的左子树上,说明要RL旋转
            if(value < rt->right->value){
                rt=RightLeftRotation(rt);
            }
            else{ //插入在右子树的右子树上,说明要RR旋转
                rt=RightRightRotation(rt);
            }
        }
    }
    else{ //数据重复了
        return rt;
    }
    updateHeight(rt);
    return rt;
}
/**
 * 对以rt为根节点的树寻找拥有最大值的节点
 * @param rt 要找的树
 * @return 包含最大值的节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::getMax(AVLTreeNode<T> *rt) {
    if (nullptr == rt){
        return nullptr;
    }
    AVLTreeNode<T>* temp = rt;
    while (temp->right != nullptr){
        temp = temp->right;
    }
    return temp;
}
/**
 * 对以rt为根节点的树寻找拥有最小值的节点
 * @param rt 要找的树
 * @return 包含最小值的节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::getMin(AVLTreeNode<T> *rt) {
    if (nullptr == rt){
        return nullptr;
    }
    AVLTreeNode<T>* temp = rt;
    while (temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}
/**
 * 对以rt为根节点的树删除值为value的节点
 * @param rt 要删除的树
 * @param value 要删除的值
 * @return 删除节点后的树
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::remove(AVLTreeNode<T> *rt, const T &value) {
    //空树
    if(nullptr==rt){
        return rt;
    }
    else if(value<rt->value){  //要删的节点在左子树
        rt->left = remove(rt->left, value);
        //失衡
        if (getHeight(rt->right)  == getHeight(rt->left)+ 2) {
            AVLTreeNode<T>* right = rt->right;
            //右子树的左子树失衡,进行RL旋转
            if (getHeight(right->left) > getHeight(right->right)) {
                rt = RightLeftRotation(rt);
            }
                //右子树的右子树失衡,进行RR旋转
            else {
                rt = RightRightRotation(rt);
            }
        }
    }
    else if(value>rt->value){ //要删的节点在右子树
        rt->right = remove(rt->right, value);
        //失衡
        if (getHeight(rt->left) >= getHeight(rt->right)+2) {
            AVLTreeNode<T>* left = rt->left;
            //左子树的左子树失衡,进行LL旋转
            if (getHeight(left->left) >= getHeight(left->right)) {
                rt = LeftLeftRotation(rt);
            }
                //左子树的右子树失衡,进行LR旋转
            else {
                rt = LeftRightRotation(rt);
            }
        }
    }
    else{ //就删这里
        //左子树或右子树是空的
        if (nullptr == rt->left || nullptr == rt->right) {
            AVLTreeNode<T>* removeNode = rt;
            if (nullptr == rt->left){
                rt = rt->right;
            }
            else {
                rt = rt->left;
            }
            delete removeNode;
        }
        else if (getHeight(rt->left) >= getHeight(rt->right)) {  //左子树比右子树高或者一样高
            AVLTreeNode<T>* maxNode = getMax(rt->left);
            rt->value = maxNode->value;
            rt->left = remove(rt->left, maxNode->value);
        }
        else {  //右子树比左子树高
            AVLTreeNode<T>* minNode = getMin(rt->right);
            rt->value = minNode->value;
            rt->right = remove(rt->right, minNode->value);
        }
    }
    return rt;
}
/**
 * 对以rt为根节点的树进行销毁
 * @param rt 要销毁的树
 */
template<typename T>
void AVLTree<T>::destroy(AVLTreeNode<T> *rt) {
    if (nullptr == rt){
        return;
    }
    if (nullptr != rt->left){
        destroy(rt->left);
    }
    if (nullptr != rt->right){
        destroy(rt->right);
    }
    delete rt;
}
/**
 * 对以rt为根节点的树进行前序遍历
 * @param rt 根节点
 */
template<typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T> *rt) const {
    if (nullptr == rt){
        return;
    }
    std::cout << rt->value << ' ';
    if (nullptr != rt->left){
        preOrder(rt->left);
    }
    if (nullptr != rt->right){
        preOrder(rt->right);
    }
}
/**
 * 对以rt为根节点的树进行中序遍历
 * @param rt 根节点
 */
template<typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T> *rt) const {
    if (nullptr == rt){
        return;
    }
    if (nullptr != rt->left){
        inOrder(rt->left);
    }
    std::cout << rt->value << ' ';
    if (nullptr != rt->right){
        inOrder(rt->right);
    }
}
/**
 * 对以rt为根节点的树进行后序遍历
 * @param rt 根节点
 */
template<typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T> *rt) const {
    if (nullptr == rt){
        return;
    }
    if (nullptr != rt->left){
        postOrder(rt->left);
    }
    if (nullptr != rt->right){
        postOrder(rt->right);
    }
    std::cout << rt->value << ' ';
}
/**
 * 对以rt为根节点的树进行层遍历
 * @param rt 根节点
 */
template<typename T>
void AVLTree<T>::layerOrder(AVLTreeNode<T> *rt) const {
    std::queue<AVLTreeNode<T>*> q;
    if (rt != nullptr){
        q.push(rt);
    }
    while (!q.empty()) {
        AVLTreeNode<T>* temp = q.front();
        q.pop();
        std::cout << temp->value << ' ';
        if (temp->left != nullptr){
            q.push(temp->left);
        }
        if (temp->right != nullptr){
            q.push(temp->right);
        }
    }
}
/**
 * 对以rt为根节点的树查找值为value的节点
 * @param rt 根节点
 * @param value 查找的值
 * @return 包含value的节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::search(AVLTreeNode<T> *rt, const T &value) const {
    while (rt != nullptr && value != rt->value) {
        if (value < rt->value){
            rt = rt->left;
        }
        else if (value > rt->value){
            rt = rt->right;
        }
        else{
            break;
        }
    }
    return rt;
}

template<typename T>
AVLTree<T>::AVLTree():root(nullptr) {}

template<typename T>
AVLTree<T>::~AVLTree() {
    destroy();
}
/**
 * 销毁树
 */
template<typename T>
void AVLTree<T>::destroy() {
    destroy(root);
}

template<typename T>
size_t AVLTree<T>::getHeight() const {
    if (nullptr == root){
        return 0;
    }
    return root->height;
}
/**
 * 插入值为value的节点
 * @param value 要插入的值
 */
template<typename T>
void AVLTree<T>::insert(const T &value) {
    root=insert(root,value);
}
/**
 * 删除值为value的节点
 * @param value 要删除的值
 */
template<typename T>
void AVLTree<T>::remove(const T &value) {
    root=remove(root,value);
}
/**
 * 前序遍历
 */
template<typename T>
void AVLTree<T>::preOrder() const {
    preOrder(root);
    std::cout<<std::endl;
}
/**
 * 中序遍历
 */
template<typename T>
void AVLTree<T>::inOrder() const {
    inOrder(root);
    std::cout<<std::endl;
}
/**
 * 后序遍历
 */
template<typename T>
void AVLTree<T>::postOrder() const {
    postOrder(root);
    std::cout<<std::endl;
}
/**
 * 层序遍历
 */
template<typename T>
void AVLTree<T>::layerOrder() const {
    layerOrder(root);
    std::cout<<std::endl;
}
/**
 * 查找值为value的节点
 * @param value 查找的值
 * @return 包含value的节点
 */
template<typename T>
AVLTreeNode<T> *AVLTree<T>::search(const T &value) const {
    return search(root, value);
}
/*
#include "AVLTree/AVLTree.cpp"
int main(){
    int arr[] = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
    AVLTree<int> t;
    for (int a : arr)
        t.insert(a);
    //7 4 2 1 3 6 5 13 11 9 8 10 12 15 14 16
    t.preOrder();
    //1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    t.inOrder();
    t.remove(13);
    //7 4 2 1 3 6 5 12 9 8 11 10 15 14 16
    t.preOrder();
    //1 2 3 4 5 6 7 8 9 10 11 12 14 15 16
    t.inOrder();
    t.remove(4);
    //7 3 2 1 6 5 12 9 8 11 10 15 14 16
    t.preOrder();
    //1 2 3 5 6 7 8 9 10 11 12 14 15 16
    t.inOrder();
    return 0;
}
 */