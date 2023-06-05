//
// Created by aaron on 2023-06-02.
//

#include <string>
#include "EMOps.h"

int EMOps::ctoi(char c) {
    return static_cast<int>(c - 'a' + 1);
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

bool EMOps::is_in_range(int num, int min, int max){
    return (num >= min) && (num <= max);
}