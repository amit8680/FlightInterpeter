//
// Created by yotamg on 15/12/2019.
//

#ifndef UNTITLED4_LEXER_H
#define UNTITLED4_LEXER_H
#include <vector>
#include "iostream"

using namespace std;

class Lexer {
public:
    vector<string> readFile(const char *fileName);
};


#endif //UNTITLED4_LEXER_H