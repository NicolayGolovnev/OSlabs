//
// Created by kolya on 18.11.2023.
//

#ifndef CLIENTRUN_H
#define CLIENTRUN_H


#include <thread>

#include "Client.h"

void SendMsgHandler(void *param) {
    Client **client = (Client **)(param);

    while (true) {
        try {
            std::string message;
            // std::cout << "> ";
            std::getline(std::cin, message);
            (*client)->send(message);
        }
        catch (std::string err) {
            std::cerr << "[CLITHR]: " << err << std::endl;
        }
    }
}

void ReceiveMsgHandler(void* param) {
    Client **client = (Client **)(param);

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

    // TODO переписать на _beginthread
    std::thread sendThread = std::thread(SendMsgHandler, &client);
    std::thread receiveThread = std::thread(ReceiveMsgHandler, &client);

    sendThread.join();
    receiveThread.join();

    // _beginthread(SendMsgHandler, 0, &client);
    // _beginthread(ReceiveMsgHandler, 0, &client);
    // Sleep(INFINITE);

    client->close();

    system("pause");

    return 0;
}

int main() {
    // Для отображения русских символов в консоли
    system("chcp 65001");

    runClientExecute();

    return 0;
}

#endif //CLIENTRUN_H