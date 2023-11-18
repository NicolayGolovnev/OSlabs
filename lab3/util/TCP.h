//
// Created by kolya on 18.11.2023.
//

#ifndef TCP_H
#define TCP_H

#include <iostream>
#include <string>

class TCP {
protected:
    virtual void connect() = 0;
    virtual void send(std::string msg) = 0;
    virtual void receive(int socket) = 0;
    virtual void close() = 0;

    virtual int getSocket() = 0;

public:
    virtual ~TCP() = default;
};

#endif //TCP_H
