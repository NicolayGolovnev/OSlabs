//
// Created by kolya on 18.11.2023.
//

#ifndef USER_H
#define USER_H

#include <string>

struct User {
    int id;
    SOCKET data;
    std::string ip;
    std::string nickname;
};

#endif //USER_H
