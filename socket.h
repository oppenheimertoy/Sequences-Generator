//
// Created by oppy on 21.04.22.
//
#ifndef CLIENT_SERVER_SOCKET_H
#define CLIENT_SERVER_SOCKET_H

// headers for working with sockets
#include <sys/types.h>
#include <sys/socket.h>

// definitions for network operations
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <string>

class Socket{
private:
    int inf_sock; //socket descriptor
public:
    Socket();
    Socket(int des_p);
    Socket(int domain, int type, int protocol); // create new socket
    ~Socket(){};
    // getter and setter
    int get_socket_inf();
    void set_socket_inf(int des_p);
    // server initialization
    void bind(sockaddr *assign_adr, socklen_t adr_len); // function associates a local address with a socket.
    void listen(const int &backlog); // listen for connections on a socket
    int accept(sockaddr *assign_adr, socklen_t *adr_len);// extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket
    // client initialization
    void connect(const sockaddr *assign_adr, const int &adr_len);
    // data transmission
    int send(const void *buf, int len, int flags); // transmit a message to another socket
    //int sendto(const void *buf, const int len, const int flags, sockaddr *src_adr, socklen_t *adr_len); //is used on a connection-mode
    int recv(void *buf, const int len, const int flags); // receiving messages from a socket
    int recvfrom(void *buf, const int len, const int flags, sockaddr *src_adr, socklen_t *adr_len);
    int write(const void *buf, const int count);
    int read(void *buf, const int count);
    // checking socket status
    bool is_valid(){
        return inf_sock != -1;
    };
    // socket functions (close and check status)
    bool status();
    void close();
};
#endif //CLIENT_SERVER_SOCKET_H
