#include "RBTree.hpp"
#include <iostream>
#include <queue>
/**
 * 根据关键字寻找节点
 * @param key 键
 * @return 节点
 */
template<typename KEY, typename VALUE>
RBTreeNode<KEY, VALUE>* RBTree<KEY, VALUE>::find(const KEY& key) const {
    RBTreeNode<KEY, VALUE>* rt = this->root;
    while (nullptr != rt) {
        //大于当前节点，往右找
        if (rt->key < key) {
            rt = rt->right;
        }
            //小于当前节点，往左
        else if (rt->key > key) {
            rt = rt->left;
        }
            //找到了
        else {

            break;
        }
    }
    return rt;
}
/**
 * 插入/更新,返回节点
 * @param key  键
 * @param value 值
 * @return 节点
 */
template<typename KEY, typename VALUE>
RBTreeNode<KEY, VALUE>* RBTree<KEY, VALUE>::insert_return(const KEY& key, const VALUE& value) {
    RBTreeNode<KEY, VALUE>* insert_parent = nullptr;
    RBTreeNode<KEY, VALUE>* temp = this->root;
    while (nullptr != temp) {
        //大于当前节点，往右找
        if (temp->key < key) {
            insert_parent = temp;
            temp = temp->right;
        }
            //小于当前节点，往左
        else if (temp->key > key) {
            insert_parent = temp;
            temp = temp->left;
        }
            //更新
        else {
            temp->value = value;
            return temp;
        }
    }
    auto* insert_node = new RBTreeNode<KEY, VALUE>(key, value, RED);
    //空树
    if (nullptr == insert_parent) {
        this->root = insert_node;
    }
    else {
        //比双亲大
        if (insert_parent->key < key) {
            insert_parent->right = insert_node;
        }
            //比双亲小
        else {
            insert_parent->left = insert_node;
        }
        insert_node->parent = insert_parent;
    }
    //修复插入的节点
    insert_fix(insert_node);
    return insert_node;
}
/**
 * 修复插入的节点
 * @param fix_node 修复节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::insert_fix(RBTreeNode<KEY, VALUE>* fix_node) {
    RBTreeNode<KEY, VALUE>* uncle = nullptr;
    //双亲节点是黑色的时候不用调整

    //调整红色节点
    while (nullptr != fix_node->parent && RED == fix_node->parent->color) {
        //插入节点双亲是左孩子
        if (fix_node->parent == fix_node->parent->parent->left) {
            //叔叔
            uncle = fix_node->parent->parent->right;
            //双亲和叔叔都是红的
            if (nullptr != uncle && RED == uncle->color) {
                //双亲和叔叔改为黑色，祖父改为红色
                fix_node->parent->color = BLACK;
                uncle->color = BLACK;
                uncle->parent->color = RED;

                //调整祖父
                fix_node = uncle->parent;
            }
            else {
                //插入节点是右孩子
                if (fix_node == fix_node->parent->right) {
                    fix_node = fix_node->parent;
                    //左旋
                    left_rotate(fix_node);
                    //调整为左孩子
                }
                //插入节点是左孩子
                fix_node->parent->color = BLACK;
                fix_node->parent->parent->color = RED;

                //右旋
                right_rotate(fix_node->parent->parent);
            }
        }
            //双亲节点的右孩子
        else {
            //叔叔
            uncle = fix_node->parent->parent->left;
            //双亲和叔叔都是红的
            if (nullptr != uncle && RED == uncle->color) {
                //双亲和叔叔改为黑色，祖父改为红色
                fix_node->parent->color = BLACK;
                uncle->color = BLACK;
                uncle->parent->color = RED;

                //调整祖父
                fix_node = uncle->parent;
            }
            else {
                //插入节点是左孩子
                if (fix_node == fix_node->parent->left) {
                    fix_node = fix_node->parent;
                    //右旋
                    right_rotate(fix_node);
                    //调整为右孩子
                }
                //插入节点是右孩子
                fix_node->parent->color = BLACK;
                fix_node->parent->parent->color = RED;

                //左旋
                left_rotate(fix_node->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}
/**
 * 左旋（相当于RR旋转）
 * @param rotate_node 旋转节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::left_rotate(RBTreeNode<KEY, VALUE>* rotate_node) {
    //不能左旋
    if (nullptr == rotate_node || nullptr == rotate_node->right) {
        return;
    }
    RBTreeNode<KEY, VALUE>* lower_right = rotate_node->right;
    lower_right->parent = rotate_node->parent;

    rotate_node->right = lower_right->left;
    if (nullptr != lower_right->left) {
        lower_right->left->parent = rotate_node;
    }
    //旋转节点是根节点
    if (nullptr == rotate_node->parent) {
        this->root = lower_right;
    }
        //旋转节点是左孩子
    else if (rotate_node == rotate_node->parent->left) {
        rotate_node->parent->left = lower_right;
    }
        //旋转节点是右孩子
    else {
        rotate_node->parent->right = lower_right;
    }
    rotate_node->parent = lower_right;
    lower_right->left = rotate_node;
}
/**
 * 右旋（相当于LL旋转）
 * @param rotate_node 旋转节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::right_rotate(RBTreeNode<KEY, VALUE>* rotate_node) {
    //不能右旋
    if (nullptr == rotate_node || nullptr == rotate_node->left) {
        return;
    }
    RBTreeNode<KEY, VALUE>* lower_left = rotate_node->left;
    rotate_node->left = lower_left->right;
    lower_left->parent = rotate_node->parent;

    if (nullptr != lower_left->right) {
        lower_left->right->parent = rotate_node;
    }
    //旋转节点是根节点
    if (rotate_node->parent == nullptr) {
        this->root = lower_left;
    }
        //旋转节点是左孩子
    else if (rotate_node == rotate_node->parent->left) {
        rotate_node->parent->left = lower_left;
    }
        //旋转节点是右孩子
    else {
        rotate_node->parent->right = lower_left;
    }
    rotate_node->parent = lower_left;
    lower_left->right = rotate_node;
}
/**
 * 找中序遍历的前驱
 * @param rt 节点
 * @return 前驱
 */
template<typename KEY, typename VALUE>
RBTreeNode<KEY, VALUE>* RBTree<KEY, VALUE>::in_order_predecessor(RBTreeNode<KEY, VALUE>* rt) const {
    //空节点
    if (rt == nullptr) {
        return nullptr;
    }
    RBTreeNode<KEY, VALUE>* predecessor = rt->left;
    //左子树存在
    if (nullptr != predecessor) {
        //左子树的最右节点（左子树最大的节点）
        while (nullptr != predecessor->right) {
            predecessor = predecessor->right;
        }
    }
    if (predecessor == nullptr) {
        RBTreeNode<KEY, VALUE>* parent = rt->parent;
        predecessor = rt;
        //找祖先，祖先左子树不包含rt
        while (parent != nullptr && parent->left == predecessor) {
            predecessor = parent;
            parent = parent->parent;
        }
        predecessor = parent;
    }
    return predecessor;
}
/**
 * 找中序遍历的后继
 * @param rt 节点
 * @return 后继
 */
template<typename KEY, typename VALUE>
RBTreeNode<KEY, VALUE>* RBTree<KEY, VALUE>::in_order_successor(RBTreeNode<KEY, VALUE>* rt) const {
    //空节点
    if (rt == nullptr) {
        return nullptr;
    }
    RBTreeNode<KEY, VALUE>* successor = rt->right;
    //右子树存在
    if (nullptr != successor) {
        //left子树的最左节点（右子树最小的节点）
        while (nullptr != successor->left) {
            successor = successor->left;
        }
    }
    if (successor == nullptr) {
        RBTreeNode<KEY, VALUE>* parent = rt->parent;
        successor = rt;
        //找祖先，祖先右子树不包含rt
        while (parent != nullptr && parent->right == successor) {
            successor = parent;
            parent = parent->parent;
        }
        successor = parent;
    }
    return successor;
}
/**
 * 前序遍历
 * @param rt 根节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::pre_order_traversal(RBTreeNode<KEY, VALUE>* rt) const {
    if (nullptr == rt) {
        return;
    }
    std::cout << '(' << (rt->color == RED ? "RED" : "BLACK") << ':' << rt->key << "->" << rt->value << ") ";
    if (nullptr != rt->left) {
        pre_order_traversal(rt->left);
    }
    if (nullptr != rt->right) {
        pre_order_traversal(rt->right);
    }
}
/**
 * 中序遍历
 * @param rt 根节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::in_order_traversal(RBTreeNode<KEY, VALUE>* rt) const {
    if (nullptr == rt) {
        return;
    }
    if (nullptr != rt->left) {
        in_order_traversal(rt->left);
    }
    std::cout << '(' << (rt->color == RED ? "RED" : "BLACK") << ':' << rt->key << "->" << rt->value << ") ";
    if (nullptr != rt->right) {
        in_order_traversal(rt->right);
    }
}
/**
 * 后序遍历
 * @param rt 根节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::post_order_traversal(RBTreeNode<KEY, VALUE>* rt) const {
    if (nullptr == rt) {
        return;
    }
    if (nullptr != rt->left) {
        post_order_traversal(rt->left);
    }
    if (nullptr != rt->right) {
        post_order_traversal(rt->right);
    }
    std::cout << '(' << (rt->color == RED ? "RED" : "BLACK") << ':' << rt->key << "->" << rt->value << ") ";
}
/**
 * 层序遍历
 * @param rt 根节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::level_order_traversal(RBTreeNode<KEY, VALUE>* rt) const {
    std::queue<RBTreeNode<KEY, VALUE>* > q;
    RBTreeNode<KEY, VALUE>* p = rt;
    if (nullptr != rt) {
        q.push(p);
    }
    while (!q.empty()) {
        p = q.front();
        q.pop();
        std::cout << '(' << (p->color == RED ? "RED" : "BLACK") << ':' << p->key << "->" << p->value << ") ";
        if (nullptr != p->left) {
            q.push(p->left);
        }
        if (nullptr != p->right) {
            q.push(p->right);
        }
    }
}
/**
 * 销毁
 * @param rt 根节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::destroy(RBTreeNode<KEY, VALUE>*& rt) {
    if (nullptr == rt) {
        return;
    }
    if (nullptr != rt->left) {
        destroy(rt->left);
    }
    if (nullptr != rt->right) {
        destroy(rt->right);
    }
    delete rt;
    rt = nullptr;
}
/**
 * 检查红黑树是否合法
 * @param rt 根节点
 * @param black_cnt 黑色节点数量
 * @return 是否合法
 */
template<typename KEY, typename VALUE>
bool RBTree<KEY, VALUE>::check(RBTreeNode<KEY, VALUE> *rt, int &black_cnt) const {
    //null节点是黑色的
    if (rt == nullptr) {
        black_cnt = 1;
        return true;
    }
    //左子树到null节点黑色节点数量
    int left_cnt = 0;
    //右子树到null节点黑色节点数量
    int right_cnt = 0;
    //左子树和右子树合法，性质5：任意一结点到每个null结点的简单路径都包含数量相同的黑结点。
    if (check(rt->right, left_cnt) && check(rt->right, right_cnt) && left_cnt == right_cnt) {
        if (BLACK == rt->color) {
            black_cnt = left_cnt + 1;
        }
            //红色节点
        else {
            black_cnt = left_cnt;
            //性质4：每个红色结点的两个子结点一定都是黑色（或者null节点）
            if (!((rt->left == nullptr || rt->left->color == BLACK) &&
                  (rt->right == nullptr || rt->right->color == BLACK))) {
                return false;
            }
        }
        return true;
    }
    return false;
}
template<typename KEY, typename VALUE>
RBTree<KEY, VALUE>::RBTree() :root(nullptr) {}
template<typename KEY, typename VALUE>
RBTree<KEY, VALUE>::~RBTree()
{
    destroy();
}
/**
 * 销毁二叉树
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::destroy() {
    if (nullptr != this->root) {
        destroy(this->root);
    }
}
/**
 * 判断二叉树是否为空
 * @return 是否为空
 */
template<typename KEY, typename VALUE>
bool RBTree<KEY, VALUE>::is_empty() const {
    return this->root == nullptr;
}

/**
 * 插入/更新
 * @param key  键
 * @param value 值
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::insert(const KEY& key, const VALUE& value) {
    insert_return(key, value);
}
/**
 * 移除节点
 * @param key
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::remove(const KEY& key) {
    RBTreeNode<KEY, VALUE>* delete_point = find(key);
    //不存在删除节点
    if (nullptr == delete_point) {
        return;
    }
    //左子树右子树非空，找找中序遍历前驱，然后删除前驱（也可以找后继）
    if (nullptr != delete_point->left && nullptr != delete_point->right) {
        //前驱
        RBTreeNode<KEY, VALUE>* predecessor = in_order_predecessor(delete_point);
        //替换
        delete_point->key = predecessor->key;
        delete_point->value = predecessor->value;
        //删除节点改为前驱
        delete_point = predecessor;
    }
    //是否创建了一个null辅助删除
    bool fake_null_flag = false;
    RBTreeNode<KEY, VALUE>* delete_point_child;
    //找孩子
    if (nullptr != delete_point->right) {
        delete_point_child = delete_point->right;
    }
    else if (nullptr != delete_point->left) {
        delete_point_child = delete_point->left;
    }
    else {
        //黑色
        delete_point_child = new RBTreeNode<KEY, VALUE>;
        fake_null_flag = true;
    }
    //更新孩子的双亲
    delete_point_child->parent = delete_point->parent;
    //删的是根
    if (nullptr == delete_point->parent) {
        this->root = delete_point_child;
    }
        //删的是右子树
    else if (delete_point == delete_point->parent->right) {
        delete_point->parent->right = delete_point_child;
    }
        //删的是左子树
    else {
        delete_point->parent->left = delete_point_child;
    }
    //删除红色不用调整，空树也不用调整

    //调整黑色的节点
    if (delete_point->color == BLACK) {
        delete_fix(delete_point_child);
    }
    //处理虚假的null
    if (fake_null_flag) {
        if (nullptr != delete_point_child->parent) {
            if (delete_point_child->parent->left == delete_point_child) {
                delete_point_child->parent->left = nullptr;
            }
            else if (delete_point_child->parent->right == delete_point_child) {
                delete_point_child->parent->right = nullptr;
            }
        }
        else {
            this->root = nullptr;
        }
        delete delete_point_child;
        delete_point_child = nullptr;
    }
    delete delete_point;
    delete_point = nullptr;
}
/**
 * 调整删除节点
 * @param fix_node 节点
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::delete_fix(RBTreeNode<KEY, VALUE>* fix_node) {
    //红色节点直接删除，根节点不用处理

    //处理非根黑色节点
    while (fix_node != this->root && BLACK == fix_node->color) {
        //删除节点是左孩子
        if (fix_node == fix_node->parent->left) {
            //兄弟节点
            RBTreeNode<KEY, VALUE>* brother = fix_node->parent->right;
            //兄弟是红的(父亲节点和兄弟的孩子均为黑色)
            if (nullptr != brother && RED == brother->color) {
                brother->color = BLACK;
                brother->parent->color = RED;
                left_rotate(fix_node->parent);
            }
                //兄弟是黑的
            else {
                //兄弟的孩子均为黑的（空的也是黑）
                if ((brother->left == nullptr || BLACK == brother->left->color) &&
                    (brother->right == nullptr || BLACK == brother->right->color)) {
                    //兄弟改成红色
                    brother->color = RED;

                    fix_node = fix_node->parent;
                }
                else {
                    //兄弟右孩子是黑的（左孩子任意）
                    if (brother->right == nullptr || BLACK == brother->right->color) {
                        brother->color = RED;
                        if (nullptr != brother->left) {
                            brother->left->color = BLACK;
                        }
                        right_rotate(brother);
                        brother = fix_node->parent->right;
                    }
                    //兄弟有黑子是红色的
                    brother->color = fix_node->parent->color;
                    brother->parent->color = BLACK;
                    if (nullptr != brother->right) {
                        brother->right->color = BLACK;
                    }
                    left_rotate(fix_node->parent);
                    fix_node = this->root;
                }
            }
        }
            //删除节点是右孩子
        else {
            //兄弟节点
            RBTreeNode<KEY, VALUE>* brother = fix_node->parent->left;
            //兄弟是红的(父亲节点和兄弟的孩子均为黑色)
            if (nullptr != brother && RED == brother->color) {
                brother->color = BLACK;
                brother->parent->color = RED;
                right_rotate(fix_node->parent);
            }
                //兄弟是黑的
            else {
                //兄弟的孩子均为黑的（空的也是黑）
                if ((brother->left == nullptr || BLACK == brother->left->color) &&
                    (brother->right == nullptr || BLACK == brother->right->color)) {
                    //兄弟改成红色
                    brother->color = RED;

                    fix_node = fix_node->parent;
                }
                else {
                    //兄弟左孩子是黑的（右孩子任意）
                    if (brother->left == nullptr || BLACK == brother->left->color) {
                        brother->color = RED;
                        if (nullptr != brother->right) {
                            brother->right->color = BLACK;
                        }
                        left_rotate(brother);
                    }
                    //兄弟有黑子是红色的
                    brother->color = fix_node->parent->color;
                    brother->parent->color = BLACK;
                    if (nullptr != brother->left) {
                        brother->left->color = BLACK;
                    }
                    right_rotate(fix_node->parent);
                    fix_node = this->root;
                }
            }
        }
    }
    fix_node->color = BLACK;
}
/**
 * 前序遍历
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::pre_order_traversal() const {
    if (nullptr != this->root) {
        pre_order_traversal(this->root);
    }
    std::cout << std::endl;
}
/**
 * 中序遍历
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::in_order_traversal() const {
    if (nullptr != this->root) {
        in_order_traversal(this->root);
    }
    std::cout << std::endl;
}
/**
 * 后序遍历
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::post_order_traversal() const {
    if (nullptr != this->root) {
        post_order_traversal(this->root);
    }
    std::cout << std::endl;
}
/**
 * 层序遍历
 */
template<typename KEY, typename VALUE>
void RBTree<KEY, VALUE>::level_order_traversal() const {
    if (nullptr != this->root) {
        level_order_traversal(this->root);
    }
    std::cout << std::endl;
}

template<typename KEY, typename VALUE>
bool RBTree<KEY, VALUE>::check() const {
    //空树
    if (nullptr == this->root) {
        return true;
    }
    //性质2：根节点是黑色的
    if (RED == this->root->color) {
        return false;
    }
    int cnt;
    return check(this->root, cnt);
}
/**
 * 如果不存在则插入key，并返回value的引用
 * @param key 键
 * @return 值
 */
template<typename KEY, typename VALUE>
VALUE &RBTree<KEY, VALUE>::operator[](const KEY &key) {
    RBTreeNode<KEY, VALUE>* rt = find(key);
    if (nullptr == rt) {
        rt = insert_return(key, VALUE());
    }
    return rt->value;
}
/*
#include <iostream>
#include "RBTree/RBTree.cpp"
using namespace std;
int main() {
    RBTree<int, int> tree;
    //12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17
    //3,7,9,11,14,15,16,18,26
    int a[] = { 12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17 };
    for (int c : a) {
        //tree.insert(c, c);
        tree[c] = c;
        cout << c << endl;
        tree.in_order_traversal();
        tree.level_order_traversal();
        cout << endl;
        if (!tree.check()) {
            cout << "faQ" << endl;
        }
    }

    for (int c : a) {
        tree.remove(c);
        cout << c << endl;
        tree.in_order_traversal();
        tree.level_order_traversal();
        cout << endl;
        if (!tree.check()) {
            cout << "faQ" << endl;
        }
    }
    return 0;
}
 */