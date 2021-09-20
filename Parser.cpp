//
// Created by amit on 20/12/2019.
//
#include <string>
#include <vector>
#include "Parser.h"
#include "Command.h"
#include "var.h"
#include "ConnectCommand.h"
#include "OpenDataServer.h"
#include "Sleep.h"
#include "Print.h"
#include "LoopCommand.h"
#include "IfCommand.h"
using namespace std;
//parsing all the commands in the txt file
void Parser::parserLexer() {
    string temp;
    this->index = 0;
    while (index < lexer.size()) {
        temp = lexer[index];
        if (this->commandsMap.find(temp) == commandsMap.end()) {
            if (this->manager->symbolMap2.find(temp) != this->manager->symbolMap2.end()) {
                Expression *exp= this->manager->l->interpret(lexer[index + 2]);
                this->manager->setSymbol(lexer[index], exp->calculate());
                index=index+2;
            }
            index++;
        } else {
            Command *command = this->commandsMap.find(temp)->second;
            index += command->execute(lexer, index);
            index++;
        }
    }
}
//constractor
Parser::Parser(vector<string> lexer1, VarManager *manager1) {
    this->lexer = lexer1;
    this->manager = manager1;
    creatCommandMap();
}
//creating map of commands
void Parser::creatCommandMap() {
    this->commandsMap["openDataServer"] = new OpenDataServer(this->manager);
    this->commandsMap["connectControlClient"] = new ConnectCommand(this->manager);
    this->commandsMap["var"] = new var(this->manager);
    this->commandsMap["Sleep"]=new Sleep(this->manager);
    this->commandsMap["Print"]=new Print(this->manager);
    this->commandsMap["while"]= new LoopCommand(this->manager, this);
    this->commandsMap["if"]=new IfCommand (this->manager, this);

}
