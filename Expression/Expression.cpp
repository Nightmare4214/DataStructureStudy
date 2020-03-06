#include "Expression.hpp"
/**
 * 获得操作符级别
 * @param op 操作符
 * @return 操作符级别
 */
int Expressions::level(const char &op) {
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
int Expressions::cmp(const char &left_operator, const char &right_operator) {
    //括号同级
    if (left_operator == '(' && right_operator == ')') {
        return 0;
    }
    else if (right_operator == '(') {
        //右边的括号一定是要先算的
        return 1;
    }
    if (level(left_operator) < level(right_operator)) {
        return 1;
    }
    //相同的操作符左边的优先级更高
    return -1;
}
/**
 * 是否是操作符
 * @param op 字符
 * @return 是否是操作符
 */
bool Expressions::is_operator(const char &op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')';
}
/**
 * 计算
 * @param left_operand 左操作数
 * @param right_operand 右操作数
 * @param op 操作符
 * @return 计算结果
 */
double Expressions::calculate(const double &left_operand, const double &right_operand, const char &op) {
    if (op == '+') {
        return left_operand + right_operand;
    }
    else if (op == '-') {
        return left_operand - right_operand;
    }
    else if (op == '*') {
        return left_operand * right_operand;
    }
    return left_operand / right_operand;
}
/**
 * 计算中缀表达式
 * @param expression 中缀表达式
 * @return 计算结果
 */
double Expressions::infix_expression(const std::string &expression) {
    //操作数栈
    std::stack<double> operands;
    //符号栈
    std::stack<char> operators;
    //表达式开始
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
                    double right_num = operands.top();
                    operands.pop();
                    double left_num = operands.top();
                    operands.pop();
                    operands.push(calculate(left_num, right_num, left_op));

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
            size_t j = i + 1;
            while ((j < expression.size() && ('0' <= expression[j] && expression[j] <= '9')) || expression[j] == '.') {
                ++j;
            }
            //操作数
            double temp = stod(expression.substr(i, j - i));
            //负数
            if (isNegative) {
                temp = -temp;
                isNegative = false;
            }
            operands.push(temp);
            i = j;
        }
    }
    char op = operators.top();
    //处理剩下的操作符
    while (op != '#') {
        double right_num = operands.top();
        operands.pop();
        double left_num = operands.top();
        operands.pop();
        operands.push(calculate(left_num, right_num, op));
        operators.pop();
        op = operators.top();
    }
    return operands.top();
}
/**
 * 中缀表达式转后缀表达式（逆波兰式）
 * @param expression 中缀表达式
 * @return 后缀表达式
 */
std::string Expressions::expression_to_rpn(const std::string &expression) {
    //后缀表达式
    std::string ans;
    //符号栈
    std::stack<char> operators;
    //是否是负数
    bool isNegative = false;
    //是否读到第一个
    bool first = true;
    //左边是否是左括号
    bool pre_left_parenthesis = false;
    size_t i = 0;
    operators.push('#');
    while (i < expression.size()) {
        //去掉多余的空格
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
                operators.pop();
                //左括号碰到了右括号
                if (cmp_result == 0) {
                    break;
                }
                else {
                    ans.push_back(' ');
                    ans.push_back(left_op);

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
            size_t j = i + 1;
            while ((j < expression.size() && ('0' <= expression[j] && expression[j] <= '9')) || expression[j] == '.') {
                ++j;
            }

            //操作数
            double temp = stod(expression.substr(i, j - i));
            //负数
            if (isNegative) {
                temp = -temp;
                isNegative = false;
            }
            ans += " ";
            ans += std::to_string(temp);
            i = j;
        }
    }
    char op = operators.top();
    //处理剩下的操作符
    while (op != '#') {
        ans.push_back(' ');
        ans.push_back(op);
        operators.pop();
        op = operators.top();
    }
    i = 0;
    //去掉前导空格
    while (i < ans.size() && ans[i] == ' ') {
        ++i;
    }
    return ans.substr(i);
}
/**
 * 计算后缀表达式（逆波兰式）
 * @param expression 后缀表达式
 * @return 计算结果
 */
double Expressions::evaluate_rpn(const std::string &expression) {
    //操作数
    std::stack<double> operands;
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
            double temp = stod(expression.substr(i, j - i));
            operands.push(temp);
            i = j;
        }
        else if (is_operator(expression[i])) {
            //计算

            double right_num = operands.top();
            operands.pop();
            double left_num = operands.top();
            operands.pop();

            operands.push(calculate(left_num, right_num, expression[i]));
            ++i;
        }

    }
    return operands.top();
}
/**
 * 中缀表达式转前缀表达式
 * @param expression 中缀表达式
 * @return 前缀表达式
 */
std::string Expressions::expression_to_pn(const std::string &expression) {
    std::stack<std::string> result;
    std::stack<char> operators;
    operators.push('#');
    bool pre_minus = false;
    int i = static_cast<int>(expression.size() - 1);
    //左边的操作数与右边的操作符对比
    auto temp_cmp = [](const char& left_operator, const char& right_operator) {
        //左边的操作数的右括号要先算
        if (left_operator == ')'){
            return 1;
        }
        else if (left_operator == '(' && right_operator == ')'){
            return 0;
        }
        //相同的左边的优先级高
        if (level(left_operator) >= level(right_operator)){
            return 1;
        }
        return -1;
    };
    //从右边往左边扫描
    while (i >= 0) {
        //去掉多余的空格
        while (i >= 0 && expression[i] == ' ') {
            --i;
        }
        //结束
        if (i < 0) {
            break;
        }
        char left_op = expression[i];
        if (is_operator(left_op)) {
            if (left_op == '-') {
                int j = i - 1;
                while (j >= 0 && expression[j] == ' ') {
                    --j;
                }
                //表达式第一个是符号
                if (j < 0) {
                    pre_minus = true;
                    break;
                }
            }
            char right_op = operators.top();
            int cmp_result = temp_cmp(left_op, right_op);
            //栈顶的操作符大于等于当前的操作符
            while (cmp_result != 1) {
                //左括号遇到右括号
                if (cmp_result == 0) {
                    operators.pop();
                    break;
                }
                else {
                    result.push(std::string(1, right_op));
                    operators.pop();
                    right_op = operators.top();
                    cmp_result = temp_cmp(left_op, right_op);
                }
            }
            if (left_op != '(') {
                operators.push(left_op);
                pre_minus = false;
                if (left_op == '-') {
                    pre_minus = true;
                }
            }
            else if (pre_minus) {
                //左括号紧贴着的是符号，所以把栈顶的操作数变成负的

                std::string t = result.top();
                result.pop();
                result.push("-" + t);
                pre_minus = false;
            }
            --i;
        }
        else {
            pre_minus = false;
            int j = i - 1;
            while (j >= 0 && (('0' <= expression[j] && expression[j] <= '9') || expression[j] == '.')) {
                --j;
            }
            result.push(expression.substr(j + 1, i - j));
            i = j;
        }
    }
    //表达式第一个是符号
    if (pre_minus) {
        operators.pop();
        std::string t = result.top();
        result.pop();
        result.push("-" + t);
    }
    char op = operators.top();
    //处理剩下的操作符
    while (op != '#') {
        result.push(std::string(1, op));
        operators.pop();
        op = operators.top();
    }
    std::string ans = result.top();
    result.pop();
    //逆序
    while (!result.empty()) {
        ans += " ";
        ans += result.top();
        result.pop();
    }
    return ans;
}
/**
 * 计算前缀表达式（波兰式）
 * @param expression 前缀表达式
 * @return 计算结果
 */
double Expressions::evaluate_pn(const std::string &expression) {
    //操作数栈
    std::stack<double> operands;
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
            double temp = stod(expression.substr(j + 1, i - j));
            operands.push(temp);
            i = j;
        }
        else if (is_operator(expression[i])) {
            double left_num = operands.top();
            operands.pop();
            double right_num = operands.top();
            operands.pop();

            operands.push(calculate(left_num, right_num, expression[i]));
            --i;
        }
    }
    return operands.top();
}
/*
#include<iostream>
#include"Expression/Expression.hpp"
using namespace std;
int main() {
    // 2-1 + 2
    //3
    cout << Expressions::infix_expression(" 2-1 + 2 ") << endl;
    //1-(2+3-(4+(5-(1-(2+4-(5+6))))))
    //-1
    cout << Expressions::infix_expression("1-(2+3-(4+(5-(1-(2+4-(5+6))))))") << endl;
    //0-2147483648
    //-2147483648
    cout << Expressions::infix_expression("0-2147483648") << endl;
    cout << Expressions::expression_to_rpn("3-4+5") << endl;
    //"2", "1", "+", "3", "*"
    cout << Expressions::evaluate_rpn("2 1 + 3 *") << endl;
    //"   (  999  /  3  /  3  /  3    )   +  (  1  +  9  /  3  )"
    //"+ / / / 999 3 3 3 + 1 / 9 3"
    //-33
    cout << Expressions::expression_to_pn("   (  999  /  3  /  3  /  3    )   +  (  1  +  9  /  3  )") << endl;
    cout << Expressions::expression_to_pn("     -999  /  3  /  3  /  3       +  (  1  +  9  /  3  )") << endl;
    cout << Expressions::evaluate_pn("+ / / / -999 3 3 3 + 1 / 9 3") << endl;
    cout << Expressions::infix_expression("   (  -999  /  3  /  3  /  3    )   +  (  1  +  9  /  3  )") << endl;
    return 0;
}
 */