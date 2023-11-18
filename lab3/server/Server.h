//
// Created by kolya on 18.11.2023.
//

#ifndef SERVER_H
#define SERVER_H

// #include <stdafx.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <string>

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>

// Отображение загрузки ws2_32.dll ws2_32.dll
#pragma comment(lib, "ws2_32.lib")

#include "../client/Client.h"
#include "../util/TCP.h"
#include "../util/User.h"
#include "../util/ClientServerHelper.h"

class Server : public TCP {
private:
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    SOCKET serverSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;

    std::string ip = SERVER_IP;
    int port = SERVER_PORT;

    std::string messageBuffer;
    int idUserCount = 0;
    std::vector<User> users;

public:
    Server() = default;

    Server(std::string _ip, int _port) {
        this->ip = _ip;
        this->port = _port;
    }

    void connect() override {
        std::cout << SERVER_MSG_PREFIX << "running server...\n";

        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            std::cout << SERVER_ERROR_MSG_PREFIX << "failure by initialize socket.\n";
            exit(EXIT_FAILURE);
            return ;
        }

        this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (this->serverSocket == SOCKET_ERROR) {
            std::cout << SERVER_ERROR_MSG_PREFIX << "establishing socket error.";
            exit(EXIT_FAILURE);
            return ;
        }

        int serverAddressLength = sizeof(this->serverAddress);
        memset(&this->serverAddress, 0, (size_t) serverAddressLength);

        int clientAddressLength = sizeof(this->clientAddress);
        memset(&this->clientAddress, 0, (size_t) clientAddressLength);

        // can use AF_INET - PF_INET defined to AF_INET (historical feature)
        // see: https://stackoverflow.com/questions/6729366/what-is-the-difference-between-af-inet-and-pf-inet-in-socket-programming
        this->serverAddress.sin_family = PF_INET;
        this->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        this->serverAddress.sin_port = htons(this->port);

        int ret = bind(this->serverSocket, reinterpret_cast<struct sockaddr*>(&this->serverAddress),
            (size_t) serverAddressLength);
        if (ret == SOCKET_ERROR) {
            std::cout << SERVER_ERROR_MSG_PREFIX << "binding connection. Socket has already establishing.\n";
            return ;
        }

        // SOMAXCONN - сколько клиентских запросов можно сохранить, что очень полезно для параллельного программирования.
        listen(this->serverSocket, SOMAXCONN);

        getsockname(this->serverSocket, reinterpret_cast<struct sockaddr*>(&this->serverAddress), &serverAddressLength);

        std::cout << SERVER_MSG_PREFIX << "started on " << inet_ntoa(this->serverAddress.sin_addr)
            << ":" << ntohs(this->serverAddress.sin_port) << std::endl;
        std::cout << SERVER_MSG_PREFIX << "listening port " << this->port << "...\n";
    };

    void accept() {
        int clientAddressLength = sizeof(this->clientAddress);
        this->clientSocket = ::accept(this->serverSocket, reinterpret_cast<struct sockaddr*>(&this->clientAddress),
            &clientAddressLength);
        getpeername(this->clientSocket, reinterpret_cast<struct sockaddr*>(&this->clientAddress),
            &clientAddressLength);

        // Print info
        std::cout << SERVER_MSG_PREFIX << "client with ip " << inet_ntoa(this->clientAddress.sin_addr)
            << ":" << ntohs(this->clientAddress.sin_port) << " was connected.\n";

        char buffer[BUFFER_SIZE] = {};
        memset(&buffer, '\0', sizeof(buffer));

        int recieveNickname = recv(this->clientSocket, buffer, BUFFER_SIZE, 0);
        if (recieveNickname != 0) {
            this->messageBuffer = buffer;

            if (this->messageBuffer.length() > 0)
                this->users.push_back(User{this->idUserCount, this->clientSocket, SERVER_IP, buffer});
            else
                std::cout << SERVER_ERROR_MSG_PREFIX << "naming nickname is empty!\n";
        }

        this->idUserCount++;
    };

    void send(std::string msg) override {
        std::cout << SERVER_MSG_PREFIX << "send message...\n";

        std::string message = "";
        std::string receiver = "";

        int index = 0;
        for (index; this->messageBuffer[index] != CLIENT_MESSAGE_DELIMITER; index++)
            receiver += this->messageBuffer[index];
        index += 1; // skip delimiter
        for (index; this->messageBuffer[index] != '\0'; index++)
            message += this->messageBuffer[index];

        // send msg to user in list
        for (int i = 0; i < users.size(); i++)
            if (this->users[i].nickname == receiver)
                ::send(this->users[i].data, message.c_str(), message.length(), 0);

        std::cout << SERVER_MSG_PREFIX << "message was sending!\n";
    };

    void receive(int socket) override {
        char buffer[BUFFER_SIZE] = {};
        memset(&buffer, '\0', sizeof(buffer));

        int receive = recv(socket, buffer, BUFFER_SIZE, 0);
        if (receive != 0) {
            std::string sender;
            std::string ip;

            for (int i = 0; i < this->users.size(); i++)
                if (this->users[i].data == socket) {
                    sender = this->users[i].nickname;
                    ip = this->users[i].ip;
                }

            this->messageBuffer = buffer;
            std::cout << SERVER_MSG_PREFIX << "message from \"" << sender << "\"(ip=" << ip << ")\n\t"
                << ">" << buffer << std::endl;
        }
        else if (receive == SOCKET_ERROR) {
            std::cout << SERVER_ERROR_MSG_PREFIX << "receiving error.\n";
            exit(EXIT_FAILURE);
        }
    };

    void close() override {
        std::cout << SERVER_MSG_PREFIX << "Stop listening!\n";
        std::cout << SERVER_MSG_PREFIX << "Stop server!\n";

        if (this->clientSocket != INVALID_SOCKET) {
            closesocket(this->clientSocket);
            this->clientSocket = INVALID_SOCKET;
        }

        if (this->serverSocket != INVALID_SOCKET) {
            closesocket(this->serverSocket);
            this->serverSocket = INVALID_SOCKET;
        }

        WSACleanup();
    };

    int getSocket() override {
        return this->clientSocket;
    };
};

#endif //SERVER_H
