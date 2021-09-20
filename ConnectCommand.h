//
// Created by amit on 24/12/2019.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H
using namespace std;

#include "VarManager.h"
#include "mutex"
#include "string"
#include "Command.h"
////connect to simulator as client
class ConnectCommand : public Command {
public:
    VarManager *manager;
    ConnectCommand(VarManager *manager1) {
        this->manager = manager1;
    }
    int execute(vector<string> lexer, int index);
    int ConnectSocket(int PORT,string temp);
    void loop(int client_socket);
};

#endif //EX3_CONNECTCOMMAND_H
