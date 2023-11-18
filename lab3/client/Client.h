//
// Created by kolya on 18.11.2023.
//

#ifndef CLIENT_H
#define CLIENT_H

// #include <stdafx.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <string>

#include <stdlib.h>
#include <stdio.h>

// Отображение загрузки ws2_32.dll ws2_32.dll
#pragma comment(lib, "ws2_32.lib")

#include "../util/TCP.h"
#include "../util/ClientServerHelper.h"

class Client : public TCP {
private:
    // Целевой адрес сервера для подключения
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    SOCKET clientSocket = 0;

    std::string ip = SERVER_IP;
    int port = SERVER_PORT;

    std::string name = "Anonymous";
    std::string companion = "Amogus";

public:
    Client(std::string _ip, int _port) {
        this->ip = _ip;
        this->port = _port;

        std::cout << CLIENT_MSG_PREFIX << "write your nickname\n" << ">";
        std::getline(std::cin, this->name);

        std::cout << CLIENT_MSG_PREFIX << "choose your companion\n" << ">";
        std::getline(std::cin, this->companion);
    };

    // Connection to server
    void connect() override {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            std::cout << CLIENT_ERROR_MSG_PREFIX << "failure by initialize socket.\n";
            exit(EXIT_FAILURE);
            return ;
        }

        this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (this->clientSocket == SOCKET_ERROR) {
            std::cout << CLIENT_ERROR_MSG_PREFIX << "establishing socket error.";
            exit(EXIT_FAILURE);
            return ;
        }

        int serverAddressLength = sizeof(this->serverAddress);
        memset(&this->serverAddress, 0, (size_t) serverAddressLength);

        int clientAddressLength = sizeof(this->clientAddress);
        memset(&this->clientAddress, 0, (size_t) clientAddressLength);

        this->serverAddress.sin_family = PF_INET;
        this->serverAddress.sin_addr.s_addr = inet_addr(this->ip.c_str());
        this->serverAddress.sin_port = htons(this->port);

        int connectionInfo = ::connect(this->clientSocket, reinterpret_cast<struct sockaddr*>(&this->serverAddress),
            serverAddressLength);
        if (connectionInfo == SOCKET_ERROR) {
            std::cout << CLIENT_ERROR_MSG_PREFIX << "connection to server error.\n";
            exit(EXIT_FAILURE);
            return ;
        }

        getsockname(this->clientSocket, reinterpret_cast<struct sockaddr*>(&this->clientAddress), &clientAddressLength);
        getpeername(this->clientSocket, reinterpret_cast<struct sockaddr*>(&this->serverAddress), &serverAddressLength);

        // sending nickname of User
        ::send(this->clientSocket, this->name.c_str(), this->name.length(), 0);

        // print info about server
        std::cout << CLIENT_MSG_PREFIX << "connected to server "
            << inet_ntoa(this->serverAddress.sin_addr) << ":" << ntohs(this->serverAddress.sin_port) << std::endl;
    };

    void send(std::string msg) override {
        std::string message = this->companion + CLIENT_MESSAGE_DELIMITER + msg;

        int __send__ = ::send(this->clientSocket, message.c_str(), message.size(), 0);
        if (__send__ == SOCKET_ERROR) {
            throw "Failure by sending a message!";
            std::cout << CLIENT_ERROR_MSG_PREFIX << "message has not sent.\n";
            return ;
        }
    };

    void receive(int socket) override {
        char buffer[BUFFER_SIZE] = {};
        memset(&buffer, '\0', sizeof(buffer));

        int __receive__ = recv(this->clientSocket, buffer, BUFFER_SIZE, 0);
        if (__receive__ == SOCKET_ERROR) {
            throw "Failure by receiving a message!";
            std::cout << CLIENT_ERROR_MSG_PREFIX << "message has not received.\n";
            return ;
        }

        std::string msg = "";
        msg += this->companion;
        msg += "> ";
        msg += buffer;

        std::cout << CLIENT_MSG_PREFIX << msg << std::endl;
    };

    void close() override {
        if (this->clientSocket != INVALID_SOCKET) {
            closesocket(this->clientSocket);
            this->clientSocket = INVALID_SOCKET;
        }

        WSACleanup();
    };

    int getSocket() override {
        return this->clientSocket;
    };
};

#endif //CLIENT_H
