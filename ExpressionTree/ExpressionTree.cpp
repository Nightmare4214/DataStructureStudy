#include "ExpressionTree.hpp"
#include <stack>
/**
 * 获得操作符级别
 * @param op 操作符
 * @return 操作符级别
 */
int ExpressionTree::level(const char &op) {
    if (op == '#') {
        return 0;
    }
    else if (op == '(' || op == ')') {
        return 1;
    }
    else if (op == '+' || op == '-') {
        return 2;
    }
    return 3;
}
/**
 * 右边的操作符与左边的操作符对比
 * @param left_operator 表达式左边的操作符
 * @param right_operator 表达式右边的操作符
 * @return 大于返回1，等于返回0，小于返回-1
 */
int ExpressionTree::cmp(const char &left_operator, const char &right_operator) {
    if (left_operator == '(' && right_operator == ')') {
        return 0;
    }
    else if (right_operator == '(') {
        return 1;
    }
    int op1_level = level(left_operator);
    int op2_level = level(right_operator);
    if (op1_level < op2_level) {
        return 1;
    }
    return -1;
}
/**
 * 是否是操作符
 * @param op 字符
 * @return 是否是操作符
 */
bool ExpressionTree::is_operator(const char &op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')';
}
/**
 * 销毁二叉树
 * @param rt 当前节点的地址
 */
void ExpressionTree::destroy(ExpressionTreeNode **rt) {
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
 * 在输出中缀表达式时是否应该添加括号
 * @param rt 根
 * @param isLeft 左子树还是右子树
 * @return 是否应该添加括号
 */
bool ExpressionTree::should_print_parenthesis(ExpressionTreeNode *rt, bool isLeft) const {
    if (rt == nullptr) {
        return false;
    }
    ExpressionTreeNode* left = rt->left;
    ExpressionTreeNode* right = rt->right;
    //叶子节点
    if (left == nullptr || right == nullptr) {
        return false;
    }
    std::string root_data = rt->data;
    std::string left_data = left->data;
    std::string right_data = right->data;
    //左子树
    if (isLeft) {
        //根是*,/时，如果左子树是+或者-，则他们优先级更高，应该先算，所以要加括号
        if (root_data == "*" || root_data == "/") {
            if (left_data == "+" || left_data == "-") {
                return true;
            }
        }
    }
    else {
        //根是-，*,/时，如果右子树是+或者-，则他们优先级更高，应该先算，所以要加括号
        if (root_data == "-" || root_data == "*" || root_data == "/") {
            if (right_data == "+" || right_data == "-") {
                return true;
            }//根是/时，如果右子树是*或者/,由于不满足结合律，所以要加括号
            else if (root_data == "/" && (right_data == "*" || right_data == "/")) {
                return true;
            }
        }
    }
    return false;
}
/**
 * 获得中缀表达式
 * @param rt 根
 * @param result 中缀表达式
 */
void ExpressionTree::get_expression(ExpressionTreeNode *rt, std::string &result) const {
    if (rt == nullptr) {
        return;
    }
    //中序遍历

    if (rt->left != nullptr) {
        if (should_print_parenthesis(rt, true)) {
            result += "(";
            get_expression(rt->left, result);
            result += ")";
        }
        else {
            get_expression(rt->left, result);
        }
    }
    result += rt->data;
    if (rt->right != nullptr) {
        if (should_print_parenthesis(rt, false)) {
            result += "(";
            get_expression(rt->right, result);
            result += ")";
        }
        else {
            get_expression(rt->right, result);
        }
    }
}
/**
 * 求表达式树的值
 * @param rt 根
 * @return 结果
 */
double ExpressionTree::getValue(ExpressionTreeNode *rt) const {
    if (rt == nullptr) {
        return 0;
    }
    double left = getValue(rt->left);
    double right = getValue(rt->right);
    std::string op = rt->data;
    if (op == "+") {
        return left + right;
    }
    else if (op == "-") {
        return left - right;
    }
    else if (op == "*") {
        return left * right;
    }
    else if (op == "/") {
        return left / right;
    }
    return stod(rt->data);
}
/**
 * 销毁二叉树
 * @param rt 当前节点的地址
 */
void ExpressionTree::destroy() {
    if (this->root != nullptr) {
        destroy(&(this->root));
    }
}

ExpressionTree::~ExpressionTree() {
    destroy();
}
/**
 * 中缀表达式生成表达式树
 * @param expression 中缀表达式
 */
void ExpressionTree::build_by_infix_expression(const std::string &expression) {
    std::stack<ExpressionTreeNode*> tree_stack;
    std::stack<char> operators;
    operators.push('#');
    //是否是负数
    bool isNegative = false;
    //是否读到第一个
    bool first = true;
    //左边是否是左括号
    bool pre_left_parenthesis = false;
    size_t i = 0;
    while (i < expression.size()) {
        //去除多余空格
        while (i < expression.size() && expression[i] == ' ') {
            ++i;
        }
        //结束
        if (i == expression.size()) {
            break;
        }
        //表达式第一个是负号
        if (expression[i] == '-' && first) {
            first = false;
            isNegative = true;
            ++i;
            continue;
        }
        first = false;
        char right_op = expression[i];
        if (is_operator(right_op)) {
            //-紧贴着左括号的话是负号
            if (right_op == '-' && pre_left_parenthesis) {
                isNegative = true;
                pre_left_parenthesis = false;
                ++i;
                continue;
            }
            pre_left_parenthesis = false;
            char left_op = operators.top();
            int cmp_result = cmp(left_op, right_op);
            //栈顶的操作符大于等于当前的操作符
            while (cmp_result != 1) {
                //左括号碰到了右括号
                if (cmp_result == 0) {
                    operators.pop();
                    break;
                }
                else {
                    ExpressionTreeNode* right = tree_stack.top();
                    tree_stack.pop();
                    ExpressionTreeNode* left = tree_stack.top();
                    tree_stack.pop();
                    tree_stack.push(new ExpressionTreeNode(left, right, left_op));

                    operators.pop();
                    left_op = operators.top();
                    cmp_result = cmp(left_op, right_op);
                }
            }
            if (right_op != ')') {
                operators.push(right_op);
                if (right_op == '(') {
                    pre_left_parenthesis = true;
                }
            }
            ++i;
        }
        else {
            pre_left_parenthesis = false;
            size_t j = i;
            //操作数
            while ((j < expression.size() && ('0' <= expression[j] && expression[j] <= '9')) || expression[j] == '.') {
                ++j;
            }
            std::string temp = expression.substr(i, j - i);
            if (isNegative) {
                temp.insert(0,"-");
                isNegative = false;
            }
            tree_stack.push(new ExpressionTreeNode(temp));
            i = j;
        }
    }
    char op = operators.top();
    //处理剩下的操作符
    while (op != '#') {
        ExpressionTreeNode* right = tree_stack.top();
        tree_stack.pop();
        ExpressionTreeNode* left = tree_stack.top();
        tree_stack.pop();
        tree_stack.push(new ExpressionTreeNode(left, right, op));
        operators.pop();
        op = operators.top();
    }
    destroy();
    this->root = tree_stack.top();
}
/**
 * 后缀表达式生成表达式树
 * @param expression 后缀表达式
 */
void ExpressionTree::build_by_rpn(const std::string &expression) {
//操作数
    std::stack<ExpressionTreeNode*> tree_stack;
    size_t i = 0;
    while (i < expression.size()) {
        //去除多余空格
        while (i < expression.size() && expression[i] == ' ') {
            ++i;
        }
        //结束
        if (i == expression.size()) {
            break;
        }
        //数字（包括负数）
        if ((expression[i] == '-' && i < expression.size() - 1 &&
             '0' <= expression[i + 1] && expression[i + 1] <= '9') ||
            ('0' <= expression[i] && expression[i] <= '9')) {
            size_t j = i + 1;
            while ((j < expression.size() && ('0' <= expression[j] && expression[j] <= '9')) || expression[j] == '.') {
                ++j;
            }
            tree_stack.push(new ExpressionTreeNode(expression.substr(i, j - i)));
            i = j;
        }
        else if (is_operator(expression[i])) {
            ExpressionTreeNode* right = tree_stack.top();
            tree_stack.pop();
            ExpressionTreeNode* left = tree_stack.top();
            tree_stack.pop();

            tree_stack.push(new ExpressionTreeNode(left, right, expression[i]));
            ++i;
        }

    }
    destroy();
    this->root = tree_stack.top();
}
/**
 * 前缀表达式生成表达式树
 * @param expression 前缀表达式
 */
void ExpressionTree::build_by_pn(const std::string &expression) {
    std::stack<ExpressionTreeNode*> tree_stack;
    int i = static_cast<int>(expression.size() - 1);
    //从右往左扫描
    while (i >= 0) {
        //去掉多余空格
        while (i >= 0 && expression[i] == ' ') {
            --i;
        }
        //结束
        if (i < 0) {
            break;
        }
        //操作数（包括负数）
        if ('0' <= expression[i] && expression[i] <= '9') {
            int j = i - 1;
            while (j >= 0 && (
                    ('0' <= expression[j] && expression[j] <= '9')
                    || expression[j] == '.'
                    || expression[j] == '-')) {
                --j;
            }
            tree_stack.push(new ExpressionTreeNode(expression.substr(j + 1, i - j)));
            i = j;
        }
        else if (is_operator(expression[i])) {
            ExpressionTreeNode* left = tree_stack.top();
            tree_stack.pop();
            ExpressionTreeNode* right = tree_stack.top();
            tree_stack.pop();

            tree_stack.push(new ExpressionTreeNode(left, right, expression[i]));
            --i;
        }
    }
    destroy();
    this->root = tree_stack.top();
}
/**
 * 获得中缀表达式
 * @return 中缀表达式
 */
std::string ExpressionTree::get_expression() const {
    std::string result;
    get_expression(this->root, result);
    return result;
}
/**
 * 获得后缀表达式
 * @return 后缀表达式
 */
std::string ExpressionTree::get_rpn() const {
    std::string result;
    bool first = true;
    std::stack<ExpressionTreeNode*> s;
    ExpressionTreeNode* p = this->root, * pre = nullptr;
    while (p != nullptr || !s.empty()) {
        //压入当前节点
        while (p != nullptr) {
            s.push(p);
            p = p->left;
        }
        p = s.top();
        //如果没有右子树或者右子树已经访问过了，那么就可以访问根节点
        if (p->right == nullptr || p->right == pre) {
            if (!first) {
                result += " ";
            }
            first = false;
            result += p->data;
            pre = p;
            s.pop();
            p = nullptr;
        }
        else {
            //访问右子树
            p = p->right;
        }
    }
    return result;
}
/**
 * 获得前缀表达式
 * @return 前缀表达式
 */
std::string ExpressionTree::get_pn() const {
    std::stack<ExpressionTreeNode*> s;
    ExpressionTreeNode* p = this->root;
    std::string result;
    bool first = true;
    while (p != nullptr || !s.empty()) {
        //一直向左子树访问
        while (p) {
            if (!first) {
                result += " ";
            }
            result += p->data;
            first = false;

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
    return result;
}
/**
 * 求表达式树的值
 * @return 结果
 */
double ExpressionTree::getValue() const {
    return getValue(this->root);
}

/*
#include <iostream>
#include "ExpressionTree/ExpressionTree.hpp"
using namespace std;
int main() {
    ExpressionTree tree;
    tree.build_by_infix_expression("0-2147483648");
    cout << tree.get_expression() << endl;
    cout << tree.get_pn() << endl;
    cout << tree.get_rpn() << endl;
    cout << tree.getValue() << endl;
    cout<<endl;

    tree.build_by_rpn("2 1 + 3 *");
    cout << tree.get_expression() << endl;
    cout << tree.get_pn() << endl;
    cout << tree.get_rpn() << endl;
    cout << tree.getValue() << endl;
    cout<<endl;

    tree.build_by_infix_expression("   (  999  /  3  /  3  /  3    )   +  (  1  +  9  /  3  ) ");
    cout << tree.get_expression() << endl;
    cout << tree.get_pn() << endl;
    cout << tree.get_rpn() << endl;
    cout << tree.getValue() << endl;
    cout<<endl;

    tree.build_by_pn("+ / / / 999 3 3 3 + 1 / 9 3");
    cout << tree.get_expression() << endl;
    cout << tree.get_pn() << endl;
    cout << tree.get_rpn() << endl;
    cout << tree.getValue() << endl;
    cout<<endl;

    tree.build_by_pn("+ / / / -999 3 3 3 + 1 / 9 3");
    cout << tree.get_expression() << endl;
    cout << tree.get_pn() << endl;
    cout << tree.get_rpn() << endl;
    cout << tree.getValue() << endl;
    return 0;
}
 */