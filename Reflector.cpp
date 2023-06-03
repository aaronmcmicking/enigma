//
// Created by aaron on 2023-06-02.
//

#include <string>
#include "Reflector.h"


Reflector::Reflector(): mapping {get_mapping('A')} {}

Reflector::Reflector(char c): mapping {get_mapping(c)} {}

void Reflector::set_reflector(char c) {
    mapping = get_mapping(c);
}

int Reflector::reflect(int in) {
    return mapping.at(in);
}

std::map<int, int> Reflector::get_mapping(char which) {
    std::map<int, int> map {};
    std::string reflection;

    switch(tolower(which)){
        case 'a':
            reflection = "EJMZALYXVBWFCRQUONTSPIKHGD";
            break;
        case 'b':
            reflection = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
            break;
        case 'c':
            reflection = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
            break;
        default:
            throw std::exception {};
            break;
    }

    for(int i {1}; i <= 26; i++){
        Operations::map_insert(map, i, static_cast<char>(tolower(reflection[i - 1])));
    }

    return map;
}