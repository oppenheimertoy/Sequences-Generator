//
// Created by oppy on 24.04.22.
//
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <sys/select.h>
#include <vector>
#include <iterator>
#include "socket.h"
#include "socket_ex.h"

const std::string LISTEN_IP = "0.0.0.0";
const std::string LISTEN_PORT = "8888";
const int  amount_of_clients = 20;

int main(){
    std::vector<int> client_sockets(amount_of_clients, 0);
    // set of sockets
    fd_set socket_descriptors;
    std::string message_server = "This is server!";
    int max_sd;
    char buffer[1025];
    struct sockaddr_in address;
   /* addrinfo hint;
    addrinfo *serverAddr = nullptr;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_flags = AI_PASSIVE;
    */
    Socket server_socket;
    try{
        Socket::get_addr_func(LISTEN_IP.c_str(), LISTEN_PORT.c_str(), &hint, &serverAddr);
        // create  server socket
        server_socket = Socket(hint.ai_family, hint.ai_socktype, hint.ai_protocol);
        server_socket.bind(serverAddr->ai_addr, sizeof(addrinfo));
        // backlog is amount of users in queue
        server_socket.listen(amount_of_clients);
        std::cout << "Waiting for connection on port " << LISTEN_PORT << std::endl;
        while(true) {
            //clear the socket set
            FD_ZERO(&socket_descriptors);
            //add server socket to set
            FD_SET(server_socket.get_socket_inf(), &socket_descriptors);
            max_sd = server_socket.get_socket_inf();
            for (auto &des_sock: client_sockets) {
                //if valid socket descriptor then add to read list
                if (des_sock) {
                    FD_SET(des_sock, &socket_descriptors);
                }
                //highest file descriptor number, need it for the select function
                if (des_sock > max_sd) {
                    max_sd = des_sock;
                }
            }
            int activity = select(max_sd + 1, &socket_descriptors, nullptr, nullptr, nullptr);
            if ((activity < 0) && (errno != EINTR)) {
                std::cout << "Select error!" << std::endl;
            }
            Socket new_user;
            if (FD_ISSET(server_socket.get_socket_inf(), &socket_descriptors)) {
                //possibly a mistake here
                new_user.set_socket_inf(server_socket.accept(serverAddr->ai_addr, sizeof(serverAddr->ai_addr))); // !!!
                std::cout << "New connection, user: " << new_user.get_socket_inf() << std::endl;
                new_user.send(message_server.c_str(), static_cast<int>(message_server.size()), 0);
                std::cout << "Welcome message sent to socket" << std::endl;
                int cnt = 0;
                for (auto &des_sock: client_sockets) {
                    if (des_sock == 0) {
                        des_sock = new_user.get_socket_inf();
                        std::cout << "Adding to list of sockets as " << cnt << std::endl;
                        break;
                    }
                    cnt++;
                }
            }
            [[maybe_unused]] int read_input;
            for (auto &des_sock: client_sockets) {
                Socket it_socket;
                it_socket.set_socket_inf(des_sock);
                int read_value; // descriptor for reading
                if (FD_ISSET(it_socket.get_socket_inf(), &socket_descriptors)) {
                    read_value = it_socket.read(buffer, 1024);
                    if (read_value == 0) {
                        //getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen));
                        std::cout << "Host disconnected" << std::endl;
                        //Close the socket and mark as 0 in list for reuse
                        if (it_socket.status()) {
                            it_socket.close();
                        }
                        des_sock = 0;
                    } else {
                        buffer[read_value] = '\0';
                        it_socket.send(buffer, strlen(buffer), 0);
                    }
                }
            }
        }
    }
    catch (SocketEx &exception_sock) {
        std::cout << exception_sock.what() << std::endl;
        std::cout << "aboba";
        if (server_socket.status()) {
            server_socket.close();
        }
        Socket::free_addr_func(serverAddr);
        return 1;
    }
    return 0;
}

