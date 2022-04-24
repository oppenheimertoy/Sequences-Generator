//
// Created by oppy on 22.04.22.
//
#include "socket_ex.h"

SocketEx::SocketEx(const char *what) : std::runtime_error(what), exception_code(0) {}

SocketEx::SocketEx(const std::string &what) : std::runtime_error(what), exception_code(0) {}

SocketEx::SocketEx(int code) : std::runtime_error(std::strerror(exception_code)), exception_code(exception_code) {}
