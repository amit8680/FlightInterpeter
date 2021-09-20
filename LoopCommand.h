//
// Created by amit on 25/12/2019.
//

#ifndef EX3_LOOPCOMMAND_H
#define EX3_LOOPCOMMAND_H

#include "VarManager.h"
#include "Command.h"
#include "Parser.h"
#include "ConditionParser.h"
class LoopCommand : public ConditionParser {
public:

    int execute(vector<string> lexer, int index);

    VarManager *manager;
    Parser *parser;
    LoopCommand(VarManager *pManager, Parser *pParser) : ConditionParser(pManager, pParser) {
        this->manager=pManager;
        this->parser=pParser;

    }
    //void work(vector<string> lexer, int index);
};


#endif //EX3_LOOPCOMMAND_H
