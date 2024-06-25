#include "RPN.hpp"

RPN::RPN(const std::string& expression) : _expression(expression)
{
    if (expression.size() == 1 && expression[0] >= '0' && expression[0] <= '9')
        throw std::runtime_error("Error: RPN does not apply to one single number");
}

RPN::RPN( const RPN& cpy ) { *this = cpy; }

RPN& RPN::operator=( const RPN& src ) { 

    if (this != &src)
    {
        _expression = src._expression; 
        _stack = src._stack;
    } 
    return *this; 
}

RPN::~RPN() {}

// -------------------------- FONCTIONS MEMBRES -------------------------- //

int RPN::calculate() {

    std::istringstream iss(_expression);
    std::string token;

    try {
        while (iss >> token) {
            processToken(token);
        }
        if (_stack.size() != 1) throw std::runtime_error("Error: not enough operators");
        return _stack.top();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

void RPN::processToken(const std::string& token) {
	
    if (token == "+" || token == "-" || token == "*" || token == "/") {
        if (_stack.size() < 2) throw std::runtime_error("Error: not enough integers in the stack");
        int b = _stack.top(); _stack.pop();
        int a = _stack.top(); _stack.pop();
        _stack.push(performOp(token, a, b));
    } else {
        int num;
        std::stringstream ss(token);
        ss >> num;
        if (ss.fail() || !ss.eof() || num < -9 || num > 9) {
            throw std::runtime_error("Error: wrong input (this program only takes int digits and operators +-*/)");
        }
        _stack.push(num);
    }
}

int RPN::performOp(const std::string& op, int a, int b) {

    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Error: impossible division");
        return a / b;
    }
    throw std::runtime_error("Error");
}