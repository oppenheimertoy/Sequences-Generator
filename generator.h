//
// Created by oppy on 25.04.22.
//
#ifndef CLIENT_SERVER_GENERATOR_H
#define CLIENT_SERVER_GENERATOR_H
#include <vector>
#include <cstdint>
#include <string>
 // this struct holds seq1, seq2 or seq3
struct sequence{
    int num_seq; // number of sequence(1, 2 or 3)
    std::vector<std::string> seq; // sequence
};

class client_seq{
private:
    // maybe it is a good idea to use hash there, in case of complexity
    std::vector<std::pair<int, sequence>> generator_file; // first -> socket descriptor
public:
    client_seq();
    ~client_seq();
    // analyse command from client
    std::string run_command(const std::string &command, int socket_num);
    std::string generate_seq(int sock_num, int num, uint64_t start, uint64_t step);
    std::string print_seq(int socket_num);
};
#endif //CLIENT_SERVER_GENERATOR_H
