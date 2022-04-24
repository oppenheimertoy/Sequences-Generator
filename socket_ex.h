//
// Created by oppy on 22.04.22.
//

#ifndef CLIENT_SERVER_SOKET_EX_H
#define CLIENT_SERVER_SOKET_EX_H

#include <stdexcept>
#include <csignal>
#include <cstring>
#include <cerrno>
#include <unistd.h>
// class for throwing errors from socket
class SocketEx : public std::runtime_error {
private:
    int exception_code; // code of throwing exception
public:
    SocketEx(const char *what);
    SocketEx(const std::string &what);
    SocketEx(int exception_code);
};
#endif //CLIENT_SERVER_SOKET_EX_H
