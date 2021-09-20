//
// Created by amit on 20/12/2019.
//

#ifndef EX3_OPENDATASERVER_H
#define EX3_OPENDATASERVER_H

using namespace std;

#include "mutex"
#include "Command.h"
#include "VarManager.h"
class OpenDataServer : public Command {
public:

    VarManager* manager;
    OpenDataServer(VarManager* manager1){
        this->manager=manager1;
    }
    int execute(vector<string> lexer, int index);
    int OpenSocket(int PORT);
    void loop(int client_socket,int socketfd);
};


#endif //EX3_OPENDATASERVER_H
