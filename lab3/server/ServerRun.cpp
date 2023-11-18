//
// Created by kolya on 18.11.2023.
//
#ifndef SERVERRUN_H
#define SERVERRUN_H

#include <thread>

#include "Server.h"

void ClientHandler(Server **server, int socket) {
    while (true) {
        (*server)->receive(socket);
        (*server)->send("__null__");
    }
}

int runServerExecute() {
    Server *server = new Server(SERVER_IP, 66010);
    server->connect();

    std::vector<std::thread> threads;

    // TODO разобраться с этой шляпой
    while (true) {
        server->accept();
        int socket = server->getSocket();
        threads.push_back(std::thread(ClientHandler, &server, socket));
    }

    std::vector<std::thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++) {
        it->join();
    }

    server->close();

    system("pause");

    return 0;
}

int main() {
    // Для отображения русских символов в консоли
    system("chcp 65001");

    runServerExecute();

    return 0;
}

#endif //SERVERRUN_H