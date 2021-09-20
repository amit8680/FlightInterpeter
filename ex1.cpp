//
// Created by yotamg on 15/11/2019.
//

#include "ex1.h"
#include "Expression.h"
#include "string"
#include <stack>
#include <queue>
#include <map>


BinaryOperator::BinaryOperator(Expression *leftExp, Expression *rightExp) {
    left = leftExp;
    right = rightExp;
}

BinaryOperator::~BinaryOperator() {
    delete (left);
    delete (right);
}


double Value::calculate() {
    return x;
}

Value::Value(double num) : x(num) {}


Variable::Variable(string name1, double value1) {
    this->name = name1;
    this->value = value1;
}

double Variable::calculate() {
    return this->value;
}

Variable &Variable::operator++() {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double num) {
    this->value += num;
    return *this;
}

Variable &Variable::operator-=(double num) {
    this->value -= num;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}


UnaryOperator::UnaryOperator(Expression *expression1) {
    this->expression = expression1;
}

UnaryOperator::~UnaryOperator() {
    delete (expression);
}


double Plus::calculate() {
    return left->calculate() + right->calculate();
}

Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}


double Minus::calculate() {
    return left->calculate() - right->calculate();
}

Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}


double Mul::calculate() {
    return left->calculate() * right->calculate();
}

Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}


double Div::calculate() {
    double rightExp = right->calculate();
    if (rightExp != 0)
        return left->calculate() / rightExp;
    else
        throw ("Divide by zero");
}

Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}


double UPlus::calculate() {
    return expression->calculate();
}

UPlus::UPlus(Expression *exp) : UnaryOperator(exp) {}


double UMinus::calculate() {
    return -(expression->calculate());
}

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {}


queue<string> Interpreter::infixToPostfix(string exp) {
    char token;
    string tokenToAdd;
    char op;
    stack<string> operatorStack;
    queue<string> outputQueue;
    map<char, int> op_precedence;
    op_precedence['+'] = 1;
    op_precedence['-'] = 1;
    op_precedence['*'] = 2;
    op_precedence['/'] = 2;
    op_precedence['#'] = 3; //plus unary
    op_precedence['@'] = 3; //minus unary
    for (unsigned int i = 0; i < exp.length(); i++) {
        token = exp[i];
        //if the token is operator
        if (isOp(token)) {
            if (tokenToAdd.length() != 0) {
                outputQueue.push(tokenToAdd); // add the number we created to the queue
                tokenToAdd.clear();
            }
            while (!operatorStack.empty()) {
                tokenToAdd = operatorStack.top();
                op = tokenToAdd[0];
                if (op == '(')
                    break;
                if (op_precedence[op] >= op_precedence[token]) {
                    operatorStack.pop();
                    outputQueue.push(tokenToAdd);
                } else
                    break;
            }
            tokenToAdd.clear();
            tokenToAdd.push_back(token);
            operatorStack.push(tokenToAdd);
            tokenToAdd.clear();
        }
        if (token == '(') {
            if (tokenToAdd.length() != 0) {
                outputQueue.push(tokenToAdd); // add the number we created to the queue
                tokenToAdd.clear();
            }
            tokenToAdd.clear();
            tokenToAdd.push_back(token);
            operatorStack.push(tokenToAdd);
            tokenToAdd.clear();
        }
        if (token == ')') {
            if (tokenToAdd.length() != 0) {
                outputQueue.push(tokenToAdd); // add the number we created to the queue
                tokenToAdd.clear();
            }
            while (!operatorStack.empty() && operatorStack.top()[0] != '(') {
                tokenToAdd = operatorStack.top();
                operatorStack.pop();
                outputQueue.push(tokenToAdd);
                tokenToAdd.clear();
            }
            //if there is no left parenthesis
            if (operatorStack.empty())
                throw ("invalid input");
            else
                operatorStack.pop();
        }
        if (isdigit(token) || token == '.') {
            tokenToAdd.push_back(token);
            if (i==exp.length()-1)
                outputQueue.push(tokenToAdd);
        }
    }
    while (!operatorStack.empty()) {
        tokenToAdd = operatorStack.top();
        operatorStack.pop();
        outputQueue.push(tokenToAdd);
    }
    return outputQueue;
}

//return true if the char is operator , else false
bool Interpreter::isOp(char c) {
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '@') || (c == '#'))
        return true;
    else
        return false;
}

// change plus unary operator to '#' and minus unary operator to '@'
void Interpreter::unaryChecker(string &expression) {
    char token;
    char prevToken = '0';
    for (unsigned int i = 0; i < expression.length(); i++) {
        token = expression[i];
        // check for unary plus
        if (token == '+') {
            if ((i == 0) || (prevToken == '('))
                expression[i] = '#';
        }
        //check for unary minus
        if (token == '-') {
            if ((i == 0) || (prevToken == '('))
                expression[i] = '@';
        }
        prevToken = token;
    }
}

Expression *Interpreter::postfixToExpression(queue<string> outputQueue) {
    stack<Expression *> helperStack;
    string exp;
    Expression *first = nullptr;
    Expression *second = nullptr;
    double num;
    while (!outputQueue.empty()) {
        exp = outputQueue.front();
        outputQueue.pop();
        //if it is number
        if (isdigit(exp[0])) {
            num = stod(exp);
            first = new Value(num);
            helperStack.push(first);
        }
        // if it is operator
        if (isOp(exp[0])) {
            switch (exp[0]) {
                case '+': {
                    // pop first element from stack
                    first = helperStack.top();
                    helperStack.pop();
                    // pop second element from stack
                    second = helperStack.top();
                    helperStack.pop();
                    helperStack.push(new Plus(second, first));
                    break;
                }
                case '-' : {
                    // pop first element from stack
                    first = helperStack.top();
                    helperStack.pop();
                    // pop second element from stack
                    second = helperStack.top();
                    helperStack.pop();
                    helperStack.push(new Minus(second, first));
                    break;
                }
                case '/' : {
                    // pop first element from stack
                    first = helperStack.top();
                    helperStack.pop();
                    // pop second element from stack
                    second = helperStack.top();
                    helperStack.pop();
                    helperStack.push(new Div(second, first));
                    break;
                }
                case '*' : {
                    // pop first element from stack
                    first = helperStack.top();
                    helperStack.pop();
                    // pop second element from stack
                    second = helperStack.top();
                    helperStack.pop();
                    helperStack.push(new Mul(second, first));
                    break;
                }
                case '@' : {
                    // pop first element from stack
                    first = helperStack.top();
                    helperStack.pop();
                    helperStack.push(new UMinus(first));
                    break;
                }
                case '#' : {
                    // pop first element from stack
                    first = helperStack.top();
                    helperStack.pop();
                    helperStack.push(new UPlus(first));
                    break;
                }
            }
        }
    }
    return helperStack.top();
}

void Interpreter::setVariables(string vars) {
    char ch;
    int pos = 0;
    string variable;
    string helper;
    double value;
    int flag = 0;
    for (unsigned int i = 0; i < vars.length(); i++) {
        ch = vars[i];
        if (ch == '=') {
            if (flag == 1)
                throw ("bad input");
            variable = vars.substr(pos, i - pos);
            if (!isValidVariable(variable))
                throw ("bad input");
            pos = i + 1;
            flag = 1;
        }
        if (ch == ';') {
            if (flag == 0)
                throw ("bad input");
            helper = vars.substr(pos, i - pos);
            pos = i + 1;
            if (isValidNumber(helper)) {
                value = stod(helper);
                this->var[variable] = value;
                flag = 0;
            } else
                throw ("bad input");
        }
        if (i == vars.length() - 1) {
            if (flag == 0)
                throw ("bad input");
            helper = vars.substr(pos, i - pos + 1);
            if (isValidNumber(helper)) {
                value = stod(helper);
                this->var[variable] = value;
                flag = 0;
            } else
                throw ("bad input");
        }
    }
}


bool Interpreter::isValidNumber(string str) {
    for (unsigned int i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-') {
            if (str.length() == 1)
                throw ("invalid input");
            else
                continue;
        }
        if (!isdigit(str[i]) && ((str[i] != '.')))
            return false;
        if (str[i] == '.') {
            if (i == 0 || i == str.length() - 1)
                return false;
            else if (!isdigit(str[i + 1]) || !isdigit(str[i - 1]))
                return false;
        }
    }
    return true;
}

bool Interpreter::isValidVariable(string var1) {
    char ch;
    if (isdigit(var1[0]))
        return false;
    for (unsigned int i = 0; i < var1.length(); i++) {
        ch = var1[i];
        if ((!isalpha(ch)) && (!isdigit(ch)) && (ch != '_'))
            return false;
    }
    return true;
}

void Interpreter::assignment(string &expression) {
    char ch;
    double num;
    string variable;
    string value;
    for (unsigned int i = 0; i < expression.length(); i++) {
        ch = expression[i];
        if (ch == '_' || isalpha(ch)) {
            variable.push_back(ch);
        }
        if (variable.length() != 0) {
            if (isdigit(ch))
                variable.push_back(ch);
        }
        if (isOp(ch) || ch == ')' || i== expression.length()-1 ) {
            if (variable.empty())
                continue;
            //check for variable name at map
            if (var.find(variable) == var.end()) {
                throw ("invalid input");
            } else {
                num=var[variable];
                if (num<0) {
                    value = to_string(var[variable]);
                    value.insert(0,"(");
                    value.push_back(')');
                    if (i== expression.length()-1)
                        expression.replace(i - variable.length()+1, variable.length(), value);
                    else
                        expression.replace(i - variable.length(), variable.length(), value);
                    variable.clear();
                }
                else {
                    value = to_string(var[variable]);
                    if (i== expression.length()-1)
                        expression.replace(i - variable.length()+1, variable.length(), value);
                    else
                        expression.replace(i - variable.length(), variable.length(), value);
                    variable.clear();
                }
            }
        }
    }
}

void Interpreter::checker(string expression) {
    char ch;
    stack<char> check;
    if (expression[0] == '*' || expression[0] == '/' || expression[0] == '.' || expression[0] == ')')
        throw ("invalid input");
    if (isOp(expression[expression.length() - 1]) || expression[expression.length() - 1] == '(' ||
        expression[expression.length() - 1] == '.')
        throw ("invalid input");
    for (unsigned int i = 0; i < expression.length(); i++) {
        ch = expression[i];
        if (!isalpha(ch) && !isdigit(ch) && ch != '_' && ch != '*' && ch != '/' && ch != '+' && ch != '-' &&
            ch != '(' && ch != ')' && ch != '.')
            throw ("invalid input");
        if (isOp(ch) && i != 0) {
            if (isOp(expression[i - 1]) || isOp(expression[i + 1]) || expression[i + 1] == '.' ||
                expression[i - 1] == '.')
                throw ("invalid input");
        }
        if (ch == '(') {
            if (i != 0) {
                if (!isOp(expression[i - 1]) && (expression[i - 1] != '('))
                    throw ("invalid input");
                if (expression[i + 1] == ')' || expression[i + 1] == '.' || expression[i - 1] == '.')
                    throw ("invalid input");
            }
            check.push(ch);
        }
        if (ch == ')') {
            if (i != expression.length() - 1) {
                if (!isOp(expression[i + 1]) && (expression[i + 1] != ')'))
                    throw ("invalid input");
            }
            if (expression[i - 1] == '.' || isOp(expression[i - 1]))
                throw ("invalid input");
            if (!check.empty()) {
                if (check.top() != '(')
                    throw ("invalid input");
                check.pop();
            } else
                throw ("invalid input");
        }
    }
    if (!check.empty())
        throw ("invalid input");
}

Expression *Interpreter::interpret(string expression) {
    if (expression.empty())
        throw ("invalid input");
    checker(expression);
    assignment(expression);
    unaryChecker(expression);
    queue<string> postfix = infixToPostfix(expression);
    Expression *exp = postfixToExpression(postfix);
    return exp;
}