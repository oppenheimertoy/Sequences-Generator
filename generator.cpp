//
// Created by oppy on 25.04.22.
//
#include <regex>
#include<iostream>
#include <cmath>

#include "generator.h"

client_seq::client_seq(){
}
client_seq::~client_seq(){
    generator_file.resize(0);
}

std::string client_seq::generate_seq(int sock_num, int num, uint64_t start, uint64_t step){
    sequence general;
    if (num < 1 || num > 3){
        return "Error_1\n";
    }
    if (step == 0){
        return "Error_2\n";
    }
    for(int i = start; i < 3000; i += step){
        general.seq.push_back(std::to_string(i));
    }
    general.num_seq = num;
    generator_file.push_back(std::make_pair(sock_num,general));
    std::cout << generator_file.size() << std::endl;
    return "Sequence generated!\n";
}

std::string client_seq::run_command(const std::string &command, int socket_num){
    static std::regex reSeqCmd("^seq(\\d) (\\d+) (\\d+)");
    static std::regex reExportCmd("^export seq");
    std::smatch pattern;
    if (regex_search(command, pattern, reSeqCmd)){
        return generate_seq(socket_num, std::stoi(pattern[1]),(uint64_t)std::stoll(pattern[2]),(uint64_t)std::stoll(pattern[3]));
    }
    if (regex_search(command, pattern, reExportCmd)){
        return print_seq(socket_num);
    }
    return "Error!_n";
}

std::string client_seq::print_seq(int socket_num){
    bool defined = false;
    sequence seq1, seq2, seq3;
    std::cout << generator_file.size() << std::endl;
    for(auto &ind : generator_file){
        if(ind.first == socket_num){
            defined = true;
        }
    }
    if (!defined){
        return "Error!_3\n";
    }
    for(auto &ind : generator_file){
        if(ind.first == socket_num){
            if(ind.second.num_seq == 1){
                seq1 = ind.second;
            }
            if(ind.second.num_seq == 2){
                seq2 = ind.second;
            }
            if(ind.second.num_seq == 3){
                seq3 = ind.second;
            }
        }
    }
    //int max = std::max(std::max(seq1.seq.size(),seq2.seq.size()), seq3.seq.size());
    std::string output_msg;
    for(int i = 0; i < 20; ++i){
        output_msg.append(seq1.seq[i]);
        output_msg.append("\t");
        output_msg.append(seq2.seq[i]);
        output_msg.append("\t");
        output_msg.append(seq3.seq[i]);
        output_msg.append("\n");
    }
    return output_msg;
}

