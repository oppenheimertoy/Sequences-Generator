//
// Created by oppy on 21.04.22.
//
#include "socket.h"
#include "socket_ex.h"
// socket headers
#include <csignal>
#include <cstring>
// header for exception
#include <cerrno>
#include <unistd.h>

static bool is_valid_param(int val_param){
    return val_param != -1;
}
Socket::Socket(){
    this -> inf_sock = 0;
}
Socket::Socket(int des_p){
    this -> inf_sock = des_p;
}
Socket::Socket(int domain, int type, int protocol){
    inf_sock = ::socket(domain, type, protocol);
    if(!is_valid_param(inf_sock)){
        throw SocketEx(errno);
    }
}
void Socket::set_socket_inf(int des_p){
    inf_sock = des_p;
}
int Socket::get_socket_inf(){
    return inf_sock;
}
void Socket::bind(sockaddr *assign_adr, socklen_t adr_len){
    int checker = ::bind(inf_sock, assign_adr, adr_len); // check if operation was successeful
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
}
void Socket::listen(const int &backlog){
    int checker = ::listen(inf_sock, backlog);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
}
void Socket::connect(const sockaddr *assign_adr, const int &adr_len){
    int checker = ::connect(inf_sock, assign_adr, adr_len);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
}
int Socket::accept(sockaddr *assign_adr, socklen_t *adr_len){
    int checker = ::accept(inf_sock, assign_adr, adr_len);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
int Socket::send(const void *buf, int len, int flags){
    int checker = ::send(inf_sock, buf, len, flags);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
/*int Socket::sendto(const void *buf, const int len, const int flags, sockaddr *src_adr, socklen_t *adr_len){
    int checker = ::sendto(inf_sock, buf, len, flags, src_adr, adr_len);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
 */
int Socket::recv(void *buf, const int len, const int flags){
    int checker = ::recv(inf_sock, buf, len, flags);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
int Socket::recvfrom(void *buf, const int len, const int flags, sockaddr *src_adr, socklen_t *adr_len){
    int checker = ::recvfrom(inf_sock, static_cast<char*>(buf), len, flags, src_adr, adr_len);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
int Socket::write(const void *buf, const int count){
    int checker = ::write(inf_sock, buf, count);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
int Socket::read(void *buf, const int count){
    int checker = ::read(inf_sock, buf, count);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    return checker;
}
bool Socket::status() {
    return is_valid_param(inf_sock) && inf_sock;
}
void Socket::close() {
    int checker = ::close(inf_sock);
    if(!is_valid_param(checker)){
        throw SocketEx(errno);
    }
    inf_sock = 0;
}