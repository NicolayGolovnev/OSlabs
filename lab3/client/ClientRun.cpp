//
// Created by kolya on 18.11.2023.
//

#ifndef CLIENTRUN_H
#define CLIENTRUN_H


#include <thread>

#include "Client.h"

void SendMsgHandler(Client **client) {
    while (true) {
        try {
            std::string message;
            std::getline(std::cin, message);
            (*client)->send(message);
        }
        catch (std::string err) {
            std::cerr << "[CLITHR]: " << err << std::endl;
        }
    }
}

void ReceiveMsgHandler(Client **client) {
    while (true) {
        try {
            (*client)->receive(0);
        }
        catch (std::string err) {
            std::cerr << "[CLITHR]: " << err << std::endl;
        }
    }
}

int runClientExecute() {
    Client *client = new Client(SERVER_IP, 66010);
    client->connect();

    std::thread sendThread = std::thread(SendMsgHandler, &client);
    std::thread receiveThread = std::thread(ReceiveMsgHandler, &client);

    sendThread.join();
    receiveThread.join();

    client->close();

    system("pause");

    return 0;
}

int main() {
    runClientExecute();

    return 0;
}

#endif //CLIENTRUN_H