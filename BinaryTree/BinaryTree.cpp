#include"BinaryTree.hpp"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

/**
 * 根据输入前序遍历创建二叉树（#表示null，节点只能是int类型）
 * @return 根节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::create_tree()
{
    std::string s;
    std::cin >> s;
    if ("#" == s) {
        return nullptr;
    }
    auto* temp = new TreeNode<T>(stoi(s));
    temp->left = create_tree();
    temp->right = create_tree();
    return temp;
}
/**
 * 根据序列创建二叉树（#表示null，节点只能是int类型，用一个空格分开）
 * @param s 序列
 * @return 根节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::create_tree(std::string& s)
{
    std::string temp_data;
    int j = 0;
    //找到下一个空格
    while (j < s.size() && s[j] != ' ') {
        ++j;
    }
    //节点信息
    temp_data = s.substr(0, j);
    if (j >= s.size()) {
        s = "";
    }
    else {
        s = s.substr(j + 1);
    }
    if ("#" == temp_data) {
        return nullptr;
    }
    auto* temp = new TreeNode<T>(stoi(temp_data));
    temp->left = create_tree(s);
    temp->right = create_tree(s);
    return temp;
}
/**
 * 前序遍历和中序遍历创建二叉树
 * @param pre_start 前序迭代器
 * @param pre_end 前序末尾
 * @param in_start 中序迭代器
 * @param in_end 中序末尾
 * @return 根节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::build_tree_with_pre_in_order(Iter pre_start,Iter pre_end,Iter in_start,Iter in_end)
{
    //没有节点了
    if (pre_end == pre_start) {
        return nullptr;
    }
    //当前节点
    T val = *pre_start;
    auto* rt = new TreeNode<T>(val);
    //找到中序遍历中当前节点位置
    Iter val_pos = find(in_start, in_end, val);
    rt->left = build_tree_with_pre_in_order(pre_start + 1, pre_start + (val_pos - in_start) + 1, in_start, val_pos);
    rt->right = build_tree_with_pre_in_order(pre_start + (val_pos - in_start) + 1, pre_end, val_pos + 1, in_end);
    return rt;
}
/**
 * 中序遍历和后序遍历创建二叉树
 * @param in_start 中序迭代器
 * @param in_end 中序末尾
 * @param post_start 后序迭代器
 * @param post_end 后序末尾
 * @return 根节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::build_tree_with_in_post_order(Iter in_start, Iter in_end, Iter post_start, Iter post_end)
{
    //没有节点了
    if (in_start == in_end) {
        return nullptr;
    }
    //当前节点
    T val = *(post_end - 1);
    auto* rt = new TreeNode<T>(val);
    //找到中序遍历中当前节点位置
    Iter val_pos = find(in_start, in_end, val);
    rt->left = build_tree_with_in_post_order(in_start, val_pos, post_start, post_start + (val_pos - in_start));
    rt->right = build_tree_with_in_post_order(val_pos + 1, in_end, post_start + (val_pos - in_start), post_end - 1);
    return rt;
}
/**
 * 根据中序遍历和后序遍历建树
 * @param level_order 层序遍历
 * @param in_order 中序遍历
 * @param in_start 中序遍历的开始位置
 * @param in_end 中序遍历结束位置
 * @return 根节点
 */
template<typename T>
TreeNode<T> *BinaryTree<T>::build_tree_with_level_in_order(
        std::vector<T> level_order,
        std::vector<T> in_order,
        int in_start,
        int in_end) {
    if(in_start>=in_end){
        return nullptr;
    }
    //当前节点
    T val=level_order[0];
    auto* rt=new TreeNode<T>(val);
    int val_pos=in_start;
    //找到当前节点值在中序遍历中的位置
    while(val_pos<in_end&&in_order[val_pos]!=val){
        ++val_pos;
    }
    //左子树的层序遍历
    std::vector<T> left;
    //右子树的层序遍历
    std::vector<T> right;
    for(size_t i=1;i<level_order.size();++i){
        int j;
        //中序遍历中，当前节点值左边的是左子树
        for(j=0;j<val_pos;++j){
            if(level_order[i] == in_order[j]){
                left.push_back(level_order[i]);
                break;
            }
        }
        //中序遍历中，当前节点值右边的是右子树
        if(j>=val_pos){
            right.push_back(level_order[i]);
        }
    }
    rt->left=build_tree_with_level_in_order(left,in_order,in_start,val_pos);
    rt->right=build_tree_with_level_in_order(right,in_order,val_pos+1,in_end);
    return rt;
}

/**
 * 销毁二叉树
 * @param rt 当前节点的地址
 */
template<typename T>
void BinaryTree<T>::destroy(TreeNode<T>** rt)
{
    if ((*rt)->left != nullptr) {
        destroy(&((*rt)->left));
    }
    if ((*rt)->right != nullptr) {
        destroy(&((*rt)->right));
    }
    delete (*rt);
    *rt = nullptr;
}
/**
 * 获得二叉树深度（只有两个节点的二叉树，深度为1）
 * @param rt 根节点
 * @return 二叉树深度
 */
template<typename T>
int BinaryTree<T>::get_depth(TreeNode<T>* rt) const
{
    if (nullptr == rt) {
        return -1;
    }
    //左子树深度
    int left_depth = get_depth(rt->left);
    //右子树深度
    int right_depth = get_depth(rt->right);
    //取较大值后+1
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}
/**
 * 前序遍历
 * @param rt 根节点
 */
template<typename T>
void BinaryTree<T>::pre_order_traversal(TreeNode<T>* rt)const
{
    std::cout << rt->data << ' ';
    if (rt->left != nullptr) {
        pre_order_traversal(rt->left);
    }
    if (rt->right != nullptr) {
        pre_order_traversal(rt->right);
    }
}
/**
 * 中序遍历
 * @param rt 根节点
 */
template<typename T>
void BinaryTree<T>::in_order_traversal(TreeNode<T>* rt)const
{
    if (rt->left != nullptr) {
        in_order_traversal(rt->left);
    }
    std::cout << rt->data << ' ';
    if (rt->right != nullptr) {
        in_order_traversal(rt->right);
    }
}
/**
 * 后序遍历
 * @param rt 根节点
 */
template<typename T>
void BinaryTree<T>::post_order_traversal(TreeNode<T>* rt)const
{
    if (rt->left != nullptr) {
        post_order_traversal(rt->left);
    }
    if (rt->right != nullptr) {
        post_order_traversal(rt->right);
    }
    std::cout << rt->data << ' ';
}
/**
 * 判断二叉树是否不含度为1的节点
 * @param rt 根节点
 * @return 是否是满二叉树（外国定义）
 */
template<typename T>
bool BinaryTree<T>::is_full_binary_tree(TreeNode<T>* rt) {
    if(nullptr == rt){
        return true;
    }
    std::queue<TreeNode<T>*> q;
    q.push(rt);
    while(!q.empty()){
        TreeNode<T>* p=q.front();
        q.pop();
        if(nullptr == p->left && p->right != nullptr){
            return false;
        }
        else if(p->left!=nullptr && nullptr == p->right){
            return false;
        }
        if(p->left!=nullptr){
            q.push(p->left);
        }
        if(p->right!=nullptr){
            q.push(p->right);
        }
    }
    return true;
}
/**
 * 计算第k层的结点数
 * @param rt 根节点
 * @param k 第k层（k>=1)
 * @return 结点数
 */
template<typename T>
int BinaryTree<T>::kth_floor_Node(TreeNode<T>* rt, const size_t& k) {
    if(0 == k || nullptr == rt){
        return 0;
    }
    std::queue<TreeNode<T>*> q;
    q.push(rt);
    size_t level=1;
    while(!q.empty()){
        int pre_level_cnt=q.size();
        //第k层
        if(k == level){
            return pre_level_cnt;
        }
        //加入这一层的节点
        while(pre_level_cnt--){
            TreeNode<T>* p=q.front();
            q.pop();
            if(p->left!=nullptr){
                q.push(p->left);
            }
            if(p->right!=nullptr){
                q.push(p->right);
            }
        }
        ++level;
    }
    return 0;
}
/**
 * 获得根节点到最近的叶子的路径长度
 * @param rt 根
 * @return 根节点到最近的叶子的路径长度
 */
template<typename T>
int BinaryTree<T>::min_depth(TreeNode<T>* rt) {
    if(nullptr == rt){
        return 0;
    }
    else if(nullptr == rt->left && nullptr == rt->right){
        return 1;
    }
    int left=0x7fffffff,right=0x7fffffff;
    if(rt->left!=nullptr){
        left=min_depth(rt->left);
    }
    if(rt->right!=nullptr){
        right=min_depth(rt->right);
    }
    return 1+(left<right?left:right);
}
/**
 * 转换为前序遍历的链表（结果只有右子树）
 * @param rt 树
 */
template<typename T>
void BinaryTree<T>::flatten(TreeNode<T> *rt) {
    TreeNode<T>* p=rt;
    while(p!=nullptr){
        if(p->left!=nullptr){
            TreeNode<T>* pre=p->left;
            //找到左子树中前序遍历的最后一个节点
            while(pre->right!=nullptr){
                pre=pre->right;
            }
            //右子树接在后面
            pre->right=p->right;
            p->right=p->left;
            p->left=nullptr;
        }
        p=p->right;
    }
}
template<typename T>
bool BinaryTree<T>::judge_root(TreeNode<T>* left, TreeNode<T>* right) {
    return (nullptr == left && nullptr == right) || (left != nullptr && right != nullptr);
}
/**
 * 判断二叉树是否对称
 * @param rt 二叉树
 * @return 是否对称
 */
template<typename T>
bool BinaryTree<T>::is_symmetric(TreeNode<T> *rt) {
    if(nullptr == rt){
        return true;
    }
    else if(!judge_root(rt->left, rt->right)){
        return false;
    }
    std::stack<TreeNode<T>* > left_tree;
    std::stack<TreeNode<T>* > right_tree;
    if(rt->left != nullptr){
        left_tree.push(rt->left);
        right_tree.push(rt->right);
    }
    while(!left_tree.empty()){
        TreeNode<T>* left=left_tree.top();
        left_tree.pop();
        TreeNode<T>* right=right_tree.top();
        right_tree.pop();

        if(left->data!=right->data){
            return false;
        }
        if(!judge_root(left->left, right->right)){
            return false;
        }
        if(left->left!= nullptr){
            left_tree.push(left->left);
            right_tree.push(right->right);
        }
        if(!judge_root(left->right, right->left)){
            return false;
        }
        if(left->right!=nullptr){
            left_tree.push(left->right);
            right_tree.push(right->left);
        }
    }
    return true;
}
/**
 * 判断是否是完全二叉树
 * @param rt 二叉树
 * @return 是否是完全二叉树
 */
template<typename T>
bool BinaryTree<T>::is_complete_binary_tree(TreeNode<T>* rt) {
    std::queue<TreeNode<T>*> q;
    q.push(rt);
    while(!q.empty()){
        TreeNode<T>* p=q.front();
        q.pop();
        if(nullptr == p)break;
        q.push(p->left);
        q.push(p->right);
    }
    while(!q.empty()){
        TreeNode<T>* p=q.front();
        q.pop();
        if(p!=nullptr)return false;
    }
    return true;
}
/**
 * 克隆二叉树
 * @param rt 二叉树
 * @return 克隆的二叉树
 */
template<typename T>
TreeNode<T> *BinaryTree<T>::cloneTree(const TreeNode<T> *rt) {
    if(nullptr == rt){
        return nullptr;
    }
    auto* clone_rt=new TreeNode<T>(rt->data);
    clone_rt->left=cloneTree(rt->left);
    clone_rt->right=cloneTree(rt->right);
    return clone_rt;
}
template<typename T>
BinaryTree<T>::BinaryTree() :root(nullptr) {}

template<typename T>
BinaryTree<T>::BinaryTree(const TreeNode<T> *src_root_node) {
    this->root=cloneTree(src_root_node);
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree &src_tree) {
    this->root=cloneTree(src_tree.root);
}

/**
 * 从二叉树构造
 * @param src 二叉树
 */
template<typename T>
void BinaryTree<T>::clone_from(const BinaryTree & src) {
    destroy();
    this->root=cloneTree(src.root);
}
/**
 * 从二叉树构造
 * @param src 根节点
 */
template<typename T>
void BinaryTree<T>::clone_from(const TreeNode<T>* src) {
    destroy();
    this->root=cloneTree(src);
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    destroy();
}
/**
 * 根据输入建树
 */
template<typename T>
void BinaryTree<T>::build_tree() {
    destroy();
    this->root = create_tree();
}
/**
 * 根据序列建树
 * @param s 序列
 */
template<typename T>
void BinaryTree<T>::build_tree(const std::string& s)
{
    destroy();
    std::string temp = s;
    this->root = create_tree(temp);
}
/**
 * 根据层序建树
 */
template<typename T>
void BinaryTree<T>::build_tree_level()
{
    std::string temp;
    std::cin >> temp;
    if ("#" == temp) {
        return;
    }
    //销毁旧的树
    destroy();

    std::queue<TreeNode<T>*> q;
    auto* rt = new TreeNode<T>(stoi(temp));
    this->root = rt;
    q.push(rt);
    while (!q.empty()) {
        rt = q.front();
        q.pop();
        std::cin >> temp;
        if (temp != "#") {
            rt->left = new TreeNode<T>(stoi(temp));
            q.push(rt->left);
        }
        std::cin >> temp;
        if (temp != "#") {
            rt->left = new TreeNode<T>(stoi(temp));
            q.push(rt->right);
        }
    }
}
/**
 * 根据层序的序列建树
 * @param s 序列
 */
template<typename T>
void BinaryTree<T>::build_tree_level(const std::string& s)
{
    size_t i = 0;
    //找下一个空格
    while (i != s.size() && s[i] != ' ') {
        ++i;
    }
    //当前节点信息
    std::string temp = s.substr(0, i);
    if ("#" == temp) {
        return;
    }
    //销毁旧的树
    destroy();

    std::queue<TreeNode<T>*> q;
    auto* rt = new TreeNode<T>(stoi(temp));
    this->root = rt;
    ++i;
    if (i >= s.size()) {
        return;
    }
    q.push(rt);
    while (!q.empty()) {
        rt = q.front();
        q.pop();
        size_t j = i;
        //找下一个空格
        while (j != s.size() && s[j] != ' ') {
            ++j;
        }
        //左子树节点信息
        temp = s.substr(i, j - i);
        if (temp != "#") {
            rt->left = new TreeNode<T>(stoi(temp));
            q.push(rt->left);
        }
        ++j;
        if (j >= s.size()) {
            return;
        }
        i = j;
        //找下一个空格
        while (j != s.size() && s[j] != ' ') {
            ++j;
        }
        //右子树节点信息
        temp = s.substr(i, j - i);
        if (temp != "#") {
            rt->right = new TreeNode<T>(stoi(temp));
            q.push(rt->right);
        }
        i = j + 1;
        if (i >= s.size()) {
            return;
        }
    }
}
/**
 * 序列化
 * @return 序列
 */
template<typename T>
std::string BinaryTree<T>::serialize()const
{
    TreeNode<T>* p;
    std::string result;
    std::queue<TreeNode<T>*> q;
    if (this->root != nullptr) {
        q.push(this->root);
        result += std::to_string(this->root->data);
    }
    //层序遍历
    while (!q.empty()) {
        p = q.front();
        q.pop();
        if (nullptr == p->left) {
            result += " #";
        }
        else {
            q.push(p->left);
            result += " " + std::to_string(p->left->data);
        }
        if (nullptr == p->right) {
            result += " #";
        }
        else {
            q.push(p->right);
            result += " " + std::to_string(p->right->data);
        }
    }
    return result;
}
/**
 * 根据前序遍历和中序遍历建树
 * @param pre_order 前序遍历
 * @param in_order 中序遍历
 * @return 根节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::build_tree_with_pre_in_order(std::vector<T> pre_order, std::vector<T> in_order)
{
    return build_tree_with_pre_in_order(pre_order.begin(), pre_order.end(), in_order.begin(), in_order.end());
}
/**
 * 根据中序遍历和后序遍历建树
 * @param in_order 中序遍历
 * @param post_order 后序遍历
 * @return 根节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::build_tree_with_in_post_order(std::vector<T> in_order, std::vector<T> post_order)
{
    return build_tree_with_in_post_order(in_order.begin(), in_order.end(), post_order.begin(), post_order.end());
}
/**
 * 用层序遍历和中序遍历建树
 * @param level_order 层序遍历
 * @param in_order 中序遍历
 * @return 根节点
 */
template<typename T>
TreeNode<T> *BinaryTree<T>::build_tree_with_level_in_order(std::vector<T> level_order, std::vector<T> in_order) {
    return build_tree_with_level_in_order(level_order,in_order,0,in_order.size());
}
/**
 * 根据前序遍历和中序遍历建树
 * @param pre_order 前序遍历
 * @param in_order 中序遍历
 */
template<typename T>
void BinaryTree<T>::build_with_pre_in_order(std::vector<T> pre_order, std::vector<T> in_order)
{
    destroy();
    this->root = build_tree_with_pre_in_order(pre_order, in_order);
}
/**
 * 根据中序遍历和后序遍历建树
 * @param in_order 中序遍历
 * @param post_order 后序遍历
 */
template<typename T>
void BinaryTree<T>::build_with_in_post_order(std::vector<T> in_order, std::vector<T> post_order)
{
    destroy();
    this->root = build_tree_with_in_post_order(in_order, post_order);
}
/**
 * 用层序遍历和中序遍历建树
 * @param level_order 层序遍历
 * @param in_order 中序遍历
 * @return 根节点
 */
template<typename T>
void BinaryTree<T>::build_with_level_post_order(std::vector<T> level_order, std::vector<T> in_order) {
    destroy();
    this->root=build_tree_with_level_in_order(level_order,in_order);
}
/**
 * 销毁二叉树
 */
template<typename T>
void BinaryTree<T>::destroy()
{
    if (this->root != nullptr) {
        destroy(&(this->root));
    }
}
/**
 * 前序遍历
 */
template<typename T>
void BinaryTree<T>::pre_order_traversal()const
{
    if (this->root != nullptr) {
        pre_order_traversal(this->root);
    }
    std::cout << std::endl;
}
/**
 * 非递归前序遍历
 */
template<typename T>
void BinaryTree<T>::pre_order_traversal_non_recursive()const
{
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* p = this->root;
    while (p != nullptr || !s.empty()) {
        //一直向左子树访问
        while (p) {
            std::cout << p->data << ' ';
            if (p->right != nullptr) {
                //存储右子树
                s.push(p->right);
            }
            p = p->left;
        }
        if (!s.empty()) {
            //右子树
            p = s.top();
            s.pop();
        }
    }
    std::cout << std::endl;
}
/**
 * 中序遍历
 */
template<typename T>
void BinaryTree<T>::in_order_traversal()const
{
    if (this->root != nullptr) {
        in_order_traversal(this->root);
    }
    std::cout << std::endl;
}
/**
 * 非递归中序遍历
 */
template<typename T>
void BinaryTree<T>::in_order_traversal_non_recursive()const
{
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* p = this->root;
    while (p != nullptr || !s.empty()) {
        //压入当前节点
        while (p != nullptr) {
            s.push(p);
            p = p->left;
        }
        //左子树已经访问完了，开始访问根
        if (!s.empty()) {
            p = s.top();
            s.pop();
            std::cout << p->data << ' ';
            //右子树
            p = p->right;
        }
    }
    std::cout << std::endl;
}
/**
 * 后序遍历
 */
template<typename T>
void BinaryTree<T>::post_order_traversal()const
{
    if (this->root != nullptr) {
        post_order_traversal(this->root);
    }
    std::cout << std::endl;
}
/**
 * 非递归后序遍历
 */
template<typename T>
void BinaryTree<T>::post_order_traversal_non_recursive()const
{
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* p = this->root, *pre = nullptr;
    while (p != nullptr || !s.empty()) {
        //压入当前节点
        while (p!=nullptr) {
            s.push(p);
            p = p->left;
        }
        p = s.top();
        //如果没有右子树或者右子树已经访问过了，那么就可以访问根节点
        if (nullptr == p->right || p->right == pre) {
            std::cout << p->data << ' ';
            pre = p;
            s.pop();
            p = nullptr;
        }
        else {
            //访问右子树
            p = p->right;
        }
    }
    std::cout << std::endl;
}
/**
 * 非递归后序遍历
 */
template<typename T>
void BinaryTree<T>::post_order_traversal_non_recursive2()const
{
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* p = this->root, * pre = nullptr;
    if (nullptr == p)return;
    s.push(p);
    while (!s.empty()) {
        p = s.top();
        //没有左子树和右子树，或者上次访问的的节点是左子树或右子树
        if ((nullptr == p->left && nullptr == p->right) ||
            ((p->left == pre || p->right == pre) && pre != nullptr)) {
            std::cout << p->data << ' ';
            pre = p;
            s.pop();
        }
        else {
            //先压入右子树，再压入左子树，这样取的时候是反过来的
            if (p->right != nullptr) {
                s.push(p->right);
            }
            if (p->left != nullptr) {
                s.push(p->left);
            }
        }
    }
    std::cout << std::endl;
}
/**
 * 非递归后序遍历
 */
template<typename T>
void BinaryTree<T>::post_order_traversal_non_recursive3()const
{
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* p = this->root, *pre = nullptr;
    //一直往左子树访问
    while (p != nullptr) {
        s.push(p);
        p = p->left;
    }
    while (!s.empty()) {
        p = s.top();
        //如果右子树为空或者访问过，则可以访问根
        if (nullptr == p->right || p->right == pre) {
            std::cout << p->data << ' ';
            s.pop();
            pre = p;
        }
        else {
            //访问右子树
            p = p->right;
            //一直往左子树访问
            while (p) {
                s.push(p);
                p = p->left;
            }
        }
    }
    std::cout << std::endl;
}
/**
 * 非递归后序遍历
 */
template<typename T>
void BinaryTree<T>::post_order_traversal_non_recursive4()const
{
    std::stack<TreeNode<T>*> s;
    //当前节点的右子树是否访问过的栈
    std::stack<bool> visited;
    bool flag;
    TreeNode<T>* p = this->root;
    while (p != nullptr || !s.empty()) {
        //一直往左子树访问
        while (p) {
            s.push(p);
            //还没有访问过右子树
            visited.push(false);
            p = p->left;
        }
        p = s.top();
        flag = visited.top();
        //右子树为空或访问过了
        if (nullptr == p->right || flag) {
            std::cout << p->data << ' ';
            s.pop();
            visited.pop();
            p = nullptr;
        }
        else {
            p = p->right;
            visited.pop();
            //访问过右子树
            visited.push(true);
        }
    }
    std::cout << std::endl;
}
/**
 * 层序遍历
 */
template<typename T>
void BinaryTree<T>::level_order_traversal()const
{
    std::queue<TreeNode<T>*> q;
    if (this->root != nullptr) {
        q.push(this->root);
    }
    TreeNode<T>* p;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        std::cout << p->data << ' ';
        if (p->left != nullptr) {
            q.push(p->left);
        }
        if (p->right != nullptr) {
            q.push(p->right);
        }
    }
    std::cout << std::endl;
}
/**
 * 取出含目标值的节点（如果有多个，则取层序遍历最前的）
 * @param target 目标值
 * @return 含目标值的节点
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::find_one(const T& target)const
{
    std::queue<TreeNode<T>*> q;
    if (this->root != nullptr) {
        q.push(this->root);
    }
    TreeNode<T>* p;
    while (!q.empty()) {
        p = q.front();
        if (p->data == target) {
            return p;
        }
        q.pop();
        if (p->left != nullptr) {
            q.push(p->left);
        }
        if (p->right != nullptr) {
            q.push(p->right);
        }
    }
    return nullptr;
}
/**
 * 最近公共祖先
 * @param rt 根节点
 * @param A 节点1
 * @param B 节点2
 * @return 最近公共祖先
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::lowest_common_ancestor(TreeNode<T>* rt, TreeNode<T>* A, TreeNode<T>* B)
{
    //不含目标节点
    if (nullptr == rt) {
        return nullptr;
    }
    else if (rt == A || rt == B) {
        //含有目标节点
        return rt;
    }
    //向左子树访问
    TreeNode<T>* left = lowest_common_ancestor(rt->left, A, B);
    //向右子树访问
    TreeNode<T>* right = lowest_common_ancestor(rt->right, A, B);

    //最近公共祖先
    if (left != nullptr && right != nullptr) {
        return rt;
    }
    else if (left != nullptr) {
        //返回左子树
        return left;
    }
    //返回右子树
    return right;
}
/**
 * 最近公共祖先
 * @param A 节点1
 * @param B 节点2
 * @return 最近公共祖先
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::lowest_common_ancestor(TreeNode<T>* A, TreeNode<T>* B)const
{
    return lowest_common_ancestor(this->root, A, B);
}
/**
* 获得二叉树深度（只有两个节点的二叉树，深度为1）
* @return 二叉树深度
*/
template<typename T>
int BinaryTree<T>::get_depth() const
{
    return get_depth(this->root);
}
/**
 * 判断二叉树是否不含度为1的节点
 * @return 是否是满二叉树（外国定义）
 */
template<typename T>
bool BinaryTree<T>::is_full_binary_tree() const {
    return is_full_binary_tree(this->root);
}
/**
 * 计算第k层的结点数
 * @param k 第k层（k>=1)
 * @return 结点数
 */
template<typename T>
int BinaryTree<T>::kth_floor_Node(const size_t& k) const {
    return kth_floor_Node(this->root,k);
}
/**
 * 获得根节点到最近的叶子的路径长度
 * @return 根节点到最近的叶子的路径长度
 */
template<typename T>
int BinaryTree<T>::min_depth() const {
    return min_depth(this->root);
}
/**
 * 转换为前序遍历的链表（结果只有右子树）
 */
template<typename T>
void BinaryTree<T>::flatten() {
    flatten(this->root);
}
/**
 * 将二叉树拷贝出去
 */
template<typename T>
TreeNode<T>* BinaryTree<T>::clone() const {
    return cloneTree(this->root);
}
/**
 * 判断是否对称
 * @return 是否对称
 */
template<typename T>
bool BinaryTree<T>::is_symmetric() const {
    return is_symmetric(this->root);
}

template<typename T>
bool BinaryTree<T>::is_complete_binary_tree() const {
    return is_complete_binary_tree(this->root);
}