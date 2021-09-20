//
// Created by amit on 23/12/2019.
//

#ifndef EX3_PRINT_H
#define EX3_PRINT_H


#include "Command.h"
#include "VarManager.h"
class Print: public Command {
public:
    VarManager* manager;
    Print(VarManager* manager1){
        this->manager=manager1;
    }
    int execute(vector<string> lexer, int index);

};


#endif //EX3_PRINT_H
