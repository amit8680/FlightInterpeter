//
// Created by amit on 22/12/2019.
//

#ifndef EX3_VARINFO_H
#define EX3_VARINFO_H
using namespace std;

#include "string"
//struct that use us to keep information of one variable
class VarInfo{
public:
    string name;
    string sim;//the adress in the XML text
    double value;
    int kriha;
    VarInfo( double value1, int kriha1,string name1){
        this->value=value1;
        this->kriha=kriha1;//the diraction of the information-0-in 1-out 2-non(like h0)
        this->name=name1;
    }

};
#endif //EX3_VARINFO_H
