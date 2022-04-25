//
// Created by oppy on 25.04.22.
//
#include <regex>
#include<iostream>
#include <cmath>
#include <limits.h>

#include "generator.h"

const unsigned long long MAX_NUM = 100;

client_seq::client_seq(){
}
client_seq::~client_seq(){
    generator_file.resize(0);
}
std::string client_seq::generate_seq(int sock_num, int num, uint64_t start, uint64_t step){
    sequence general;
    std::string success_message = "Sequence ";
    success_message = success_message + std::to_string(num);
    success_message += " generated!\n";
    if (num < 1 || num > 3){
        return "Error! You can only choose seq1, seq2 or seq3\n";
    }
    if (step == 0 || start == 0){
        return "Error! Invalid params\n";
    }
    for(unsigned long long i = start; i < MAX_NUM; i += step){
        general.seq.push_back(std::to_string(i));
    }
    general.num_seq = num;
    generator_file.push_back(std::make_pair(sock_num,general));
    return success_message;
}

std::string client_seq::run_command(const std::string &command, int socket_num){
    static std::regex regular_seq("^seq(\\d) (\\d+) (\\d+)");
    static std::regex regular_export("^export seq");
    std::smatch pattern;
    if (regex_search(command, pattern, regular_seq)){
        return generate_seq(socket_num, std::stoi(pattern[1]),(uint64_t)std::stoll(pattern[2]),(uint64_t)std::stoll(pattern[3]));
    }
    if (regex_search(command, pattern, regular_export)){
        return print_seq(socket_num);
    }
    return "Error! Wrong command\n";
}

std::string client_seq::print_seq(int socket_num){
    bool defined = false;
    sequence seq1, seq2, seq3;
    for(auto &ind : generator_file){
        if(ind.first == socket_num){
            defined = true;
        }
    }
    if (!defined){
        return "Error! Sequences were not generated\n";
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
    int max = std::max(std::max(seq1.seq.size(),seq2.seq.size()), seq3.seq.size());
    std::string output_msg;
    for(int i = 0; i < max; ++i){
        if(seq1.seq.size() > i){
            output_msg.append(seq1.seq[i]);
        }else{
            output_msg.append(" ");
        }
        output_msg.append("\t");
        if(seq2.seq.size() > i){
            output_msg.append(seq2.seq[i]);
        }else{
            output_msg.append(" ");
        }
        output_msg.append("\t");
        if(seq3.seq.size() > i){
            output_msg.append(seq3.seq[i]);
        }else{
            output_msg.append(" ");
        }
        output_msg.append("\n");
    }
    return output_msg;
}

