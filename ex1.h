//
// Created by amit on 25/12/2019.
//

#ifndef EX3_EX1_H
#define EX3_EX1_H
#include <map>
#include <string>
#include <queue>
#include "Expression.h"


class BinaryOperator : public Expression {
protected :
    Expression *left;
    Expression *right;
public:
    BinaryOperator(Expression *leftExp, Expression *rightExp);

    virtual ~BinaryOperator();
};
class Value : public Expression {
    const double x;
public:
    Value(double num) ;
    double calculate() ;
};

class Variable: public Expression {
    string name;
    double value;
public:
    Variable (string name,double value) ;
    double calculate() ;
    Variable& operator++ () ;
    Variable& operator-- () ;
    Variable& operator+= (double num) ;
    Variable& operator-= (double num) ;
    Variable& operator++ (int) ;
    Variable& operator-- (int) ;
};

class UnaryOperator : public Expression {
protected :
    Expression* expression;

public:
    UnaryOperator(Expression* expression) ;
    virtual ~UnaryOperator() ;
};

class Plus : public BinaryOperator {
    double calculate() ;
public:
    Plus (Expression* left, Expression* right) ;
};

class Minus : public BinaryOperator {
    double calculate();
public:
    Minus (Expression* left, Expression* right) ;
};

class Mul : public BinaryOperator {

    double calculate() ;
public:
    Mul (Expression* left, Expression* right) ;
};

class Div : public BinaryOperator {

    double calculate() ;
public:
    Div (Expression* left, Expression* right) ;
};

class UPlus : public UnaryOperator {
    double calculate() ;
public:
    UPlus (Expression* exp);
};

class UMinus : public UnaryOperator {
    double calculate() ;
public:
    UMinus (Expression* exp) ;
};
class Interpreter {
    map<string, double> var;

public:
    queue<string> infixToPostfix(string exp) ;
    bool isOp (char c) ;
    void unaryChecker (string& expression) ;
    Expression* postfixToExpression (queue <string> outputQueue) ;
    void setVariables(string vars) ;
    bool isValidNumber (string str) ;
    bool isValidVariable (string var) ;
    void assignment (string& expression);
    void checker (string expression);
    Expression* interpret (string expression);

};

#endif //EX3_EX1_H
