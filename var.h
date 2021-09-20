//
// Created by amit on 20/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H

#include "VarInfo.h"
#include "string"
#include "unordered_map"
#include "Command.h"
#include "VarManager.h"

using namespace std;
class var: public Command {
public:

    VarManager* manager;
    var(VarManager* manager1){
        this->manager=manager1;

    }
    int execute(vector<string> lexer,int index);



};


#endif //EX3_VAR_H
