//
// Created by yotamg on 24/12/2019.
//
#include "Lexer.h"
#include <fstream>
#include <vector>
#include "iostream"

using namespace std;
vector<string> Lexer::readFile(const char *fileName) {
    int flag=0;
    ifstream myfile;
    myfile.open(fileName,ios::in);
    if (!myfile) {
        throw "cant open file";
    }
    vector<string> lexer;
    string str;
    string temp = "";
    while (getline(myfile, str)) {
        flag=0;
        for (unsigned int i = 0; i < str.length(); i++) {
            if (!lexer.empty()) {
                if (lexer.back()=="while" || lexer.back()=="if") {
                    flag=3;
                }
                if (lexer.back()=="Print") {
                    flag=4;
                }
            }
            // normal mode
            if (flag==0) {
                if (isalpha(str[i]) || isdigit(str[i])) {
                    temp += str[i];
                }
                if (str[i] == ' ' || str[i]== '\t'){
                    if (!temp.empty())
                        lexer.push_back(temp);
                    temp = "";
                }
                if (str[i] == '=') {
                    if (!temp.empty())
                        lexer.push_back(temp);
                    temp = "";
                    temp.push_back(str[i]);
                    lexer.push_back(temp);
                    temp = "";
                    flag = 1;
                }
                if (str[i]== '(') {
                    if (!temp.empty())
                        lexer.push_back(temp);
                    flag=2;
                    temp="";
                }
                if (str[i]== '-' && i!=0 && i!=str.length()-1) {
                    if (str[i-1]=='<') {
                        if (!temp.empty())
                            lexer.push_back(temp);
                        temp="<-";
                        lexer.push_back(temp);
                        temp="";
                    }
                    else if (str[i+1]=='>') {
                        if (!temp.empty())
                            lexer.push_back(temp);
                        temp="->";
                        lexer.push_back(temp);
                        temp="";
                    }
                    else {
                        temp.push_back(str[i]);
                    }
                }
                if (str[i]=='+' || str[i]=='/' || str[i]== '*') {
                    temp.push_back(str[i]);
                }
                if (str[i]== '{' || str[i]=='}') {
                    if (!temp.empty())
                        lexer.push_back(temp);
                    temp="";
                    temp.push_back(str[i]);
                }
            }
                // after equation mode
            else if (flag==1) {
                if (str[i]!= ' ' && str[i] != '\t')
                    temp+=str[i];
            }
                // while and if
            else if (flag==3) {
                if (str[i]!= ' ' && str[i]!= '\t' && str[i]!='{')
                    temp+=str[i];
                if (str[i]=='{') {
                    flag=0;
                    lexer.push_back(temp);
                    temp="{";
                    lexer.push_back(temp);
                    temp="";
                }
            }
                // print command
            else if (flag==4) {
                if (i!=str.length()-1)
                    temp+=str[i];
            }
                // expression mode
            else if (flag ==2) {
                if (str[i]== ')') {
                    flag=0;
                    lexer.push_back(temp);
                    temp="";
                }
                else if (str[i]== ',') {
                    if (!temp.empty())
                        lexer.push_back(temp);
                    temp="";
                }
                else if (str[i] == ' ' || str[i]== '\t') {
                    // do nothing
                }
                else
                {
                    temp += str[i];
                }
            }
            // check for end of line
            if (i==str.length()-1) {
                flag = 0;
                if (!temp.empty())
                    lexer.push_back(temp);
                temp="";
            }
        }
    }
    myfile.close();
    return lexer;
}