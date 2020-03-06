#pragma once
#include <string>
#include <stack>
class Expressions {
private:
    static int level(const char&);
    static int cmp(const char&, const char&);
    static bool is_operator(const char&);
    static double calculate(const double& left_operand, const double& right_operand, const char& op);
public:
    static double infix_expression(const std::string&);
    static std::string expression_to_rpn(const std::string&);
    static double evaluate_rpn(const std::string&);
    static std::string expression_to_pn(const std::string&);
    static double evaluate_pn(const std::string&);
};