//
// Created by amit on 02/01/2020.
//

#include "Command.h"
#include "VarManager.h"
#include <string>
#include "ConditionParser.h"
#include <vector>
//parser for the scoope command-if and will
void ConditionParser::Cparser(vector<string> lexer, int index) {
    int myindex = 0;
    myindex = index;
    int temp2 = 0;
    if (lexer[myindex] == "{") {
        myindex++;
    }
    while (lexer[myindex] != "}") {
        string temp = lexer[myindex];
        if (this->manager->symbolMap2.find(temp) != this->manager->symbolMap2.end()) {
            Expression *exp = nullptr;
            exp = this->manager->l->interpret(lexer[myindex + 2]);
            this->manager->setSymbol(lexer[myindex], exp->calculate());
            myindex = myindex + 2;
        } else if (this->parser->commandsMap.find(temp) != this->parser->commandsMap.end()) {
            Command *command = this->parser->commandsMap.find(temp)->second;
            temp2 = command->execute(lexer, myindex);
            myindex += temp2;
        }
        myindex++;
    }
}
//parsing the condition of the loop to expressions and operator
vector<string> ConditionParser::myCondition(string s) {
    vector<string> condition;
    int flag = 0;
    string condi = s;
    string temp = "";
    string temp2 = "";
    string oper = "";
    for (unsigned int i = 0; i < condi.size(); i++) {
        if (flag == 0) {
            if (condi[i] != '<' && condi[i] != '>' && condi[i] != '=' && condi[i] != '!') {
                if (condi[i] != ' ') {
                    temp += condi[i];
                }
            } else {
                flag = 1;
                if (condi[i] != ' ') {
                    oper += condi[i];
                }
                if (condi[i + 1] == '=') {
                    oper += condi[i + 1];
                    i++;
                }
            }
        } else if (flag == 1) {
            if (condi[i] != ' ') {
                temp2 += condi[i];
            }
        }
    }
    condition.push_back(temp);
    condition.push_back(oper);
    condition.push_back(temp2);
    return condition;
}
//checking if the condition is ture or not
//recining vector with the expressions and operator
bool ConditionParser::isConditionTrue(vector<string> condi) {
    Expression *exp1 = this->manager->l->interpret(condi[0]);
    Expression *exp2 = this->manager->l->interpret(condi[2]);
    if (condi[1] == "<") {
        if (exp1->calculate() < exp2->calculate()) {
            return true;
        }
    } else if (condi[1] == "<=") {
        if (exp1->calculate() <= exp2->calculate()) {
            return true;
        }
    } else if (condi[1] == ">") {
        if (exp1->calculate() > exp2->calculate()) {
            return true;
        }
    } else if (condi[1] == ">=") {
        if (exp1->calculate() >= exp2->calculate()) {
            return true;
        }
    } else if (condi[1] == "==") {
        //for double rounds problems
        if (exp1->calculate() - exp2->calculate() < 0.000001 && exp1->calculate() - exp2->calculate() > -0.000001) {
            return true;
        }
    } else if (condi[1] == "!=") {
        if (exp1->calculate() != exp2->calculate()) {
            return true;
        }
    }
    return false;
}
