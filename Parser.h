//
// Created by amit on 20/12/2019.
//

#ifndef EX3_PARSER_H
#define EX3_PARSER_H
#include <vector>
#include "mutex"
#include "Command.h"
#include "unordered_map"
#include "VarManager.h"
using namespace std;


class Parser {
public:
    VarManager* manager;
    Parser(vector<string> lexer,VarManager* manager1);
    void creatCommandMap();
    void parserLexer();
    unsigned int index;
    unordered_map<string, Command*> commandsMap;
    vector<string> lexer;
    ~Parser(){
        for (auto itr = commandsMap.begin(); itr != commandsMap.end(); ++itr) {
            delete(itr->second);
        }
    }
};


#endif //EX3_PARSER_H
