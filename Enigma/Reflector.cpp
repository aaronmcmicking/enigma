//
// Created by aaron on 2023-06-02.
//

#include <iostream>
#include <string>
#include "Headers/Reflector.h"


Reflector::Reflector(): mapping {get_mapping('A')} {}

Reflector::Reflector(char c): mapping {get_mapping(c)} {}

void Reflector::set_reflector(char c) {
    mapping = get_mapping(c);
}

void Reflector::set_reflector(Reflector r) {
    for(int i {}; i < CONVERSION_MAP_ARRAY_SIZE; i++) {
        mapping[i] = r.mapping[i];
    }
}

int Reflector::reflect(int input) {
    return mapping[input];
}

int* Reflector::get_mapping(char which) {
    static int map[CONVERSION_MAP_ARRAY_SIZE] {};
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
            std::cout << "invalid reflector code" << std::endl;
            throw std::exception {};
            break;
    }

    for(int i {Rotor::min_position}; i <= Rotor::max_position; i++){
        map[i] = stdeo::ctoi(static_cast<char>(tolower(reflection.at(i - 1))));
    }

    return map;
}