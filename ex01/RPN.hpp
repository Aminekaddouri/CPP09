#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>

class RPN {
public:
    RPN();
    double evaluate(const std::string &expression);
private:
    bool isOperator(const std::string &token);
    double performOperation(double a, double b, const std::string &op);
};

#endif // RPN_HPP
