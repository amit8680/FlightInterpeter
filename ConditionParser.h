//
// Created by amit on 30/12/2019.
//

#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include "Command.h"
#include "VarManager.h"
#include "Parser.h"
#include <string>
#include <iostream>
#include "ConnectCommand.h"
#include <vector>

//the will and if command father class
class ConditionParser : public Command {
public:
    //pointer for the class with all the variables information
    VarManager *manager;
    Parser *parser;
    //constructor
    ConditionParser(VarManager *manager1, Parser *parser1) {
        this->manager = manager1;
        this->parser = parser1;
    }
    //parser for the scoope command-if and will
    void Cparser(vector<string> lexer, int index);
    //parsing the condition of the loop to expressions and operator
    vector<string> myCondition(string s);
    //checking if the condition is ture or not
    bool isConditionTrue(vector<string> condi);
};

#endif //EX3_CONDITIONPARSER_H
