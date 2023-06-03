//
// Created by aaron on 2023-06-02.
//

#include <string>
#include "Operations.h"

int Operations::ctoi(char c) {
    return static_cast<int>(c - 'a' + 1);
}

char Operations::itoc(int i) {
    return static_cast<char>(i + 'a' - 1);
}

std::pair<int, int> Operations::pair(int k, int v) {
    return std::pair<int, int>{k, v};
}

void Operations::map_insert(std::map<int, int> &map, int k, char v) {
    map.insert(pair(k, ctoi(v)));
}

std::string Operations::strip_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

bool Operations::is_in_range(int num, int min, int max){
    return (num >= min) && (num <= max);
}