//
// Created by aaron on 2023-06-02.
//

#include <string>
#include "Headers/EMOps.h"

int EMOps::ctoi(char c) {
    return (tolower(c) - 'a' + 1);
}

char EMOps::itoc(int i) {
    return static_cast<char>(i + 'a' - 1);
}

std::string EMOps::strip_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

// inclusive
bool EMOps::is_in_range(int num, int min, int max){
    return (num >= min) && (num <= max);
}

void EMOps::rep_arr3(int dest[3], const int* src){
    for(int i {0}; i < 3; i++) dest[i] = src[i];
}

void EMOps::rep_arr3(int dest[3], int a, int b, int c){
    int src[] {a, b, c};
    rep_arr3(dest, src);
}