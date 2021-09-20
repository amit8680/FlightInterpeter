//
// Created by amit on 23/12/2019.
//

#include <chrono>
#include <thread>
#include <iostream>
#include "Sleep.h"
#include <algorithm>
//sleep command
int Sleep::execute(vector<string> lexer, int index) {
    string temp = lexer[index + 1];
    temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
    Expression *exp = this->manager->l->interpret(temp);
    int x = exp->calculate();
    //sleeping this thread for time that we get in milliseconds
    this_thread::sleep_for(std::chrono::milliseconds(x));
    return 1;
}