//
// Created by amit on 20/12/2019.
//

#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <regex>
#include "OpenDataServer.h"

using namespace std;

int OpenDataServer::execute(vector<string> lexer, int index) {
    Expression *exp = this->manager->l->interpret(lexer[index + 1]);
    int PORT = exp->calculate();
    OpenSocket(PORT);
    return 1;
}

int OpenDataServer::OpenSocket(int PORT) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    thread first((&OpenDataServer::loop), this, client_socket, socketfd);
    first.detach();

    return 2;
}

void OpenDataServer::loop(int client_socket, int socketfd) {
    regex reg("^[-+]?[0-9]+(\\.[0-9]+)?$");
    while (this->manager->flag == 1) {
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        char *temp = strtok(buffer, "\n");
        char *token = strtok(temp, ",");
        int i = 0;
        while (token != NULL && i < 36) {
            if (manager->pathMap.find(manager->xmlList[i]) != manager->pathMap.end()) {
                if (regex_match(token, reg)) {
                    if (manager->symbolMap2[manager->pathMap[manager->xmlList[i]]->name]->kriha == 0) {
                        this->manager->setSymbol(manager->symbolMap2[manager->pathMap[manager->xmlList[i]]->name]->name,
                                                 stod(token));
                    }
                }
            }
            token = strtok(NULL, ",");
            i++;
        }
    }
    close(socketfd);
}
