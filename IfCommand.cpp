//
// Created by amit on 25/12/2019.
//

#include <iostream>
#include "IfCommand.h"
#include "ex1.h"
//excacute to if scope
int IfCommand::execute(vector<string> lexer, int index) {
    int count = 0;
    vector<string> condition = myCondition(lexer[index + 1]);
    if (isConditionTrue(condition)) {
        //if the condition is true parsing the commands inside
        Cparser(lexer, index + 2);
    }
    index = index + 2;
    while (lexer[index] != "}") {
        count++;
        index++;
    }
    return count + 2;
}


