//
// Created by amit on 20/12/2019.
//
#include <unistd.h>
#include "Lexer.h"
#include "var.h"
#include "ConnectCommand.h"

//creating new vaibles
int var::execute(vector<string> lexer, int index) {
    index++;
    if (lexer[index + 1] == "=") {
        Expression *exp = this->manager->l->interpret(lexer[index + 2]);
        this->manager->addTomaps(lexer[index], "-", exp->calculate(), 2);
        string temp = lexer[index] + "=" + to_string(exp->calculate());
        this->manager->l->setVariables(temp);
        return 3;
    }
    if (lexer[index + 1] == "->") {
        this->manager->addTomaps(lexer[index], lexer[index + 3], 0, 1);
        return 4;
    }
    if (lexer[index + 1] == "<-") {
        this->manager->addTomaps(lexer[index], lexer[index + 3], 0, 0);
        return 4;
    }
}


