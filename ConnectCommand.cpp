//
// Created by amit on 21/12/2019.
//
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include "ConnectCommand.h"
#include <algorithm>

using namespace std;

//the client side, we connect to the simulator to send commands
int ConnectCommand::execute(vector<string> lexer, int index) {
    Expression *exp = this->manager->l->interpret(lexer[index + 2]);
    int PORT = exp->calculate();
    string temp = lexer[index + 1];
    temp.erase(std::remove(temp.begin(), temp.end(), '"'), temp.end());
    //this thread use for sending command to the airplain untill the end will the parserer keep working
    ConnectSocket(PORT, temp);
    return 2;
}

int ConnectCommand::ConnectSocket(int PORT, string temp) {
    const char *adress = const_cast<char *>(temp.c_str());
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(adress);  //the localhost address
    address.sin_port = htons(PORT);
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server" << std::endl;
    }
    thread second((&ConnectCommand::loop), this, client_socket);
    second.detach();
    return 0;
}
//running and sending imformation to the server untill the program ends
void ConnectCommand::loop(int client_socket) {
    //sending messages will the program stop
    while (this->manager->flag == 1) {
        if (!this->manager->commandQ.empty()) {
            string message = this->manager->commandQ.front();
            //cout << message << endl;
            write(client_socket, message.c_str(), message.length());
            this->manager->commandQ.pop();
        }
    }
    close(client_socket);
}