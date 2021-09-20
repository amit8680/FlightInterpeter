//
// Created by amit on 23/12/2019.
//

#ifndef EX3_SLEEP_H
#define EX3_SLEEP_H


#include "Command.h"
#include "VarManager.h"

class Sleep : public Command {
public:
    VarManager *manager;
    Sleep(VarManager *manager1) {
        this->manager = manager1;
    }
    int execute(vector<string> lexer, int index);
};


#endif //EX3_SLEEP_H
