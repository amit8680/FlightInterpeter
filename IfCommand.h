//
// Created by amit on 27/12/2019.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H

#include "VarManager.h"
#include "Command.h"
#include "Parser.h"
#include "ConditionParser.h"
class IfCommand : public ConditionParser {
public:
    int execute(vector<string> lexer, int index);
    VarManager *manager;
    Parser *parser;
    IfCommand(VarManager *pManager, Parser *pParser) : ConditionParser(pManager, pParser) {
        this->manager=pManager;
        this->parser=pParser;

    }
    //void work(vector<string> lexer, int index);
};


#endif //EX3_IFCOMMAND_H
