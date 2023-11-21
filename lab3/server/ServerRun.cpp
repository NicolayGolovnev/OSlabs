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

    // TODO разобраться с этой шляпой
    while (true) {
        server->accept();
        int socket = server->getSocket();
        std::thread client = std::thread(ClientHandler, &server, socket);
        // Отсоединяем , так как если сделаем .join(),
        // то будем ожидать, пока данный поток завершится
        client.detach();
    }

    server->close();

    system("pause");

    return 0;
}

int main() {
    runServerExecute();

    return 0;
}

#endif //SERVERRUN_H