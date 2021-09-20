//
// Created by amit on 23/12/2019.
//

#ifndef EX3_VARMANAGER_H
#define EX3_VARMANAGER_H

#include "queue"
#include "VarManager.h"
#include "VarInfo.h"
#include "unordered_map"
#include "vector"
#include <string>
#include "ex1.h"
//here we get all the maps and data that we need for the program
//we will send pointer to this class from every class in the program to let them use this information
class VarManager {
public:
    int flag=0;
    void addTomap1(string str1, double val);
    VarManager();
    void setSymbol(string name, double value);
    void addTomaps(string name, string path, double val, int kriha);
    void XML();
    unordered_map<string, VarInfo*> symbolMap2;//varible map with name as key
    unordered_map<string, VarInfo*> pathMap;//variable map with adress in XML as key
    vector<string> xmlList;
    queue<string> commandQ;//queue that hold the message to the server and send them in connect command
    Interpreter *l = new Interpreter();//interpeter for expression like in ex1
    //distractor to free all memory
    ~VarManager(){
        delete (l);
        for (auto itr = pathMap.begin(); itr != pathMap.end(); ++itr) {
           delete(itr->second);
        }
    }
};


#endif //EX3_VARMANAGER_H
