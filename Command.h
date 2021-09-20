//
// Created by amit on 20/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H
#include <string>
#include "vector"
using namespace std;
//abstract class-all commands inherit it
class Command {
public:
    virtual int execute(vector<string> lexer,int index)=0;
    virtual ~Command(){

    };
};


#endif //EX3_COMMAND_H
