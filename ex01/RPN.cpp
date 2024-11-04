#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cctype>

RPN::RPN() {}

double RPN::evaluate(const std::string &expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            std::stringstream ss(token); // Create a stringstream for conversion
            double num;
            ss >> num; // Convert string to double
            stack.push(num); // Push the converted number onto the stack
        } else if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Error: not enough operands");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result = performOperation(a, b, token);
            stack.push(result);
        } else {
            throw std::runtime_error("Error");
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Error: too many operands");
    }

    return stack.top();
}

bool RPN::isOperator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double RPN::performOperation(double a, double b, const std::string &op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Error: division by zero");
        return a / b;
    }
    throw std::runtime_error("Error: unknown operator");
}
