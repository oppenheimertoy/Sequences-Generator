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
#include "generator.h"

const int LISTEN_PORT = 8888;
const int  amount_of_clients = 20;

int main(){
    std::vector<int> client_sockets(amount_of_clients, 0);
    // set of sockets
    fd_set socket_descriptors;
    std::string message_server = "You have successfully connected!\n";
    int max_sd, addrlen;
    char buffer[1025];
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( LISTEN_PORT);
    Socket server_socket;
    client_seq generator_it; // keeps all sequences
    try{
        // create  server socket
        server_socket = Socket(AF_INET , SOCK_STREAM , 0);
        server_socket.bind((struct sockaddr *)&address, sizeof(address));
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
            addrlen = sizeof(address);
            // new user connection
            if (FD_ISSET(server_socket.get_socket_inf(), &socket_descriptors)) {
                new_user.set_socket_inf(server_socket.accept((struct sockaddr *)&address, (socklen_t*)&addrlen));
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
            std::string input_buf;
            // check all user sockets status
            for (auto &des_sock: client_sockets) {
                Socket it_socket;
                it_socket.set_socket_inf(des_sock);
                int read_value; // descriptor for reading
                if (FD_ISSET(it_socket.get_socket_inf(), &socket_descriptors)) {
                    read_value = it_socket.read(buffer, 1024);
                    if (read_value == 0) {
                        std::cout << "Host disconnected" << std::endl;
                        //Close the socket and mark as 0 in list for reuse
                        if (it_socket.status()) {
                            it_socket.close();
                        }
                        des_sock = 0;
                    } else {
                        buffer[read_value] = '\0';
                        std::string output;
                        input_buf.append(buffer);
                        std::string command(input_buf.substr(0, (read_value - 2)));
                        command = command + "\n";
                        output = generator_it.run_command(command, des_sock);
                        it_socket.send(output.c_str(), (int)(output.size()), 0);
                    }
                }
            }
        }
    }
    catch (SocketEx &exception_sock) {
        std::cout << exception_sock.what() << std::endl;
        if (server_socket.status()) {
            server_socket.close();
        }
        return 1;
    }
    return 0;
}

