//
// Created by amit on 23/12/2019.
//
#include <iostream>
#include "Print.h"
#include <string>
#include <algorithm>
//print command- print to screen
int Print::execute(vector<string> lexer, int index) {
    if(lexer[index+1][0]=='"'){
        //if its a message
        string temp = lexer[index + 1];
        temp.erase(remove(temp.begin(), temp.end(), '"'), temp.end());
        cout << temp << endl;
        return 1;
    }
    else{
        //if its a varible value
        string temp = lexer[index + 1];
        temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
        Expression *exp = this->manager->l->interpret(temp);
        cout<< exp->calculate()<<endl;
        return 1;
    }


}