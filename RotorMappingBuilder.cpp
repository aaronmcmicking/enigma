//
// Created by aaron on 2023-06-01.
//

#include <map>
#include "RotorMappingBuilder.h"

bool RotorMappingBuilder::init {false};
std::map<int, int>* RotorMappingBuilder::rotor_mappings {};

std::map<int, int> RotorMappingBuilder::get_rotor_mapping(int rotor_number){
    if(!init){
        rotor_mappings = construct_rotor_mappings();
    }
    if(rotor_mappings == nullptr) throw std::exception{};
    return rotor_mappings[rotor_number - 1];
}

// converts a character to it's 1-indexed position in the alphabet
// ex: a -> 1, b -> 2, ..., z -> 26
int RotorMappingBuilder::ctoi(char c) {
    return static_cast<int>(c - 'a' + 1);
}

void RotorMappingBuilder::set_init(bool state){
    init = state;
}

// sets the rotor_mappings to null
void RotorMappingBuilder::nullify_mappings(){
    rotor_mappings = nullptr;
}

std::pair<int, int> RotorMappingBuilder::pair(int k, int v) {
    return std::pair<int, int>{k, v};
}

void RotorMappingBuilder::map_insert(std::map<int, int> &map, int k, char v) {
    map.insert(pair(k, ctoi(v)));
}

std::map<int, int> RotorMappingBuilder::get_reflector_mapping() {
    std::map<int, int> mapA {};

    map_insert(mapA, 1,  'e');
    map_insert(mapA, 2,  'j');
    map_insert(mapA, 3,  'm');
    map_insert(mapA, 4,  'z');
    map_insert(mapA, 5,  'a');
    map_insert(mapA, 6,  'l');
    map_insert(mapA, 7,  'y');
    map_insert(mapA, 8,  'x');
    map_insert(mapA, 9,  'v');
    map_insert(mapA, 10, 'b');
    map_insert(mapA, 11, 'w');
    map_insert(mapA, 12, 'f');
    map_insert(mapA, 13, 'c');
    map_insert(mapA, 14, 'r');
    map_insert(mapA, 15, 'q');
    map_insert(mapA, 16, 'u');
    map_insert(mapA, 17, 'o');
    map_insert(mapA, 18, 'n');
    map_insert(mapA, 19, 't');
    map_insert(mapA, 20, 's');
    map_insert(mapA, 21, 'p');
    map_insert(mapA, 22, 'i');
    map_insert(mapA, 23, 'k');
    map_insert(mapA, 24, 'h');
    map_insert(mapA, 25, 'g');
    map_insert(mapA, 26, 'd');

    return mapA;
}

std::map<int, int>* RotorMappingBuilder::construct_rotor_mappings() {
    // I
    std::map<int, int> mapI{};
    map_insert(mapI, 1,  'e');
    map_insert(mapI, 2,  'k');
    map_insert(mapI, 3,  'm');
    map_insert(mapI, 4,  'f');
    map_insert(mapI, 5,  'l');
    map_insert(mapI, 6,  'g');
    map_insert(mapI, 7,  'd');
    map_insert(mapI, 8,  'q');
    map_insert(mapI, 9,  'v');
    map_insert(mapI, 10, 'z');
    map_insert(mapI, 11, 'n');
    map_insert(mapI, 12, 't');
    map_insert(mapI, 13, 'o');
    map_insert(mapI, 14, 'w');
    map_insert(mapI, 15, 'y');
    map_insert(mapI, 16, 'h');
    map_insert(mapI, 17, 'x');
    map_insert(mapI, 18, 'u');
    map_insert(mapI, 19, 's');
    map_insert(mapI, 20, 'p');
    map_insert(mapI, 21, 'a');
    map_insert(mapI, 22, 'i');
    map_insert(mapI, 23, 'b');
    map_insert(mapI, 24, 'r');
    map_insert(mapI, 25, 'c');
    map_insert(mapI, 26, 'j');

    // II
    std::map<int, int> mapII{};
    map_insert(mapII, 1,  'a');
    map_insert(mapII, 2,  'j');
    map_insert(mapII, 3,  'd');
    map_insert(mapII, 4,  'k');
    map_insert(mapII, 5,  's');
    map_insert(mapII, 6,  'i');
    map_insert(mapII, 7,  'r');
    map_insert(mapII, 8,  'u');
    map_insert(mapII, 9,  'x');
    map_insert(mapII, 10, 'b');
    map_insert(mapII, 11, 'l');
    map_insert(mapII, 12, 'h');
    map_insert(mapII, 13, 'w');
    map_insert(mapII, 14, 't');
    map_insert(mapII, 15, 'm');
    map_insert(mapII, 16, 'c');
    map_insert(mapII, 17, 'q');
    map_insert(mapII, 18, 'g');
    map_insert(mapII, 19, 'z');
    map_insert(mapII, 20, 'n');
    map_insert(mapII, 21, 'p');
    map_insert(mapII, 22, 'y');
    map_insert(mapII, 23, 'f');
    map_insert(mapII, 24, 'v');
    map_insert(mapII, 25, 'o');
    map_insert(mapII, 26, 'e');

    // III
    std::map<int, int> mapIII{};
    map_insert(mapIII, 1,  'b');
    map_insert(mapIII, 2,  'd');
    map_insert(mapIII, 3,  'f');
    map_insert(mapIII, 4,  'h');
    map_insert(mapIII, 5,  'j');
    map_insert(mapIII, 6,  'l');
    map_insert(mapIII, 7,  'c');
    map_insert(mapIII, 8,  'p');
    map_insert(mapIII, 9,  'r');
    map_insert(mapIII, 10, 't');
    map_insert(mapIII, 11, 'x');
    map_insert(mapIII, 12, 'v');
    map_insert(mapIII, 13, 'z');
    map_insert(mapIII, 14, 'n');
    map_insert(mapIII, 15, 'y');
    map_insert(mapIII, 16, 'e');
    map_insert(mapIII, 17, 'i');
    map_insert(mapIII, 18, 'w');
    map_insert(mapIII, 19, 'g');
    map_insert(mapIII, 20, 'a');
    map_insert(mapIII, 21, 'k');
    map_insert(mapIII, 22, 'm');
    map_insert(mapIII, 23, 'u');
    map_insert(mapIII, 24, 's');
    map_insert(mapIII, 25, 'q');
    map_insert(mapIII, 26, 'o');

    // IV
    std::map<int, int> mapIV{};
    map_insert(mapIV, 1,  'e');
    map_insert(mapIV, 2,  's');
    map_insert(mapIV, 3,  'o');
    map_insert(mapIV, 4,  'v');
    map_insert(mapIV, 5,  'p');
    map_insert(mapIV, 6,  'z');
    map_insert(mapIV, 7,  'j');
    map_insert(mapIV, 8,  'a');
    map_insert(mapIV, 9,  'y');
    map_insert(mapIV, 10, 'q');
    map_insert(mapIV, 11, 'u');
    map_insert(mapIV, 12, 'i');
    map_insert(mapIV, 13, 'r');
    map_insert(mapIV, 14, 'h');
    map_insert(mapIV, 15, 'x');
    map_insert(mapIV, 16, 'l');
    map_insert(mapIV, 17, 'n');
    map_insert(mapIV, 18, 'f');
    map_insert(mapIV, 19, 't');
    map_insert(mapIV, 20, 'g');
    map_insert(mapIV, 21, 'k');
    map_insert(mapIV, 22, 'd');
    map_insert(mapIV, 23, 'c');
    map_insert(mapIV, 24, 'm');
    map_insert(mapIV, 25, 'w');
    map_insert(mapIV, 26, 'b');

    // V
    std::map<int, int> mapV{};
    map_insert(mapV, 1,  'v');
    map_insert(mapV, 2,  'z');
    map_insert(mapV, 3,  'b');
    map_insert(mapV, 4,  'r');
    map_insert(mapV, 5,  'g');
    map_insert(mapV, 6,  'i');
    map_insert(mapV, 7,  't');
    map_insert(mapV, 8,  'y');
    map_insert(mapV, 9,  'u');
    map_insert(mapV, 10, 'p');
    map_insert(mapV, 11, 's');
    map_insert(mapV, 12, 'd');
    map_insert(mapV, 13, 'n');
    map_insert(mapV, 14, 'h');
    map_insert(mapV, 15, 'l');
    map_insert(mapV, 16, 'x');
    map_insert(mapV, 17, 'a');
    map_insert(mapV, 18, 'w');
    map_insert(mapV, 19, 'm');
    map_insert(mapV, 20, 'j');
    map_insert(mapV, 21, 'q');
    map_insert(mapV, 22, 'o');
    map_insert(mapV, 23, 'f');
    map_insert(mapV, 24, 'e');
    map_insert(mapV, 25, 'c');
    map_insert(mapV, 26, 'k');

    // VI
    std::map<int, int> mapVI{};
    map_insert(mapVI, 1,  'j');
    map_insert(mapVI, 2,  'p');
    map_insert(mapVI, 3,  'g');
    map_insert(mapVI, 4,  'v');
    map_insert(mapVI, 5,  'o');
    map_insert(mapVI, 6,  'u');
    map_insert(mapVI, 7,  'm');
    map_insert(mapVI, 8,  'f');
    map_insert(mapVI, 9,  'y');
    map_insert(mapVI, 10, 'q');
    map_insert(mapVI, 11, 'b');
    map_insert(mapVI, 12, 'e');
    map_insert(mapVI, 13, 'n');
    map_insert(mapVI, 14, 'h');
    map_insert(mapVI, 15, 'z');
    map_insert(mapVI, 16, 'r');
    map_insert(mapVI, 17, 'd');
    map_insert(mapVI, 18, 'k');
    map_insert(mapVI, 19, 'a');
    map_insert(mapVI, 20, 's');
    map_insert(mapVI, 21, 'x');
    map_insert(mapVI, 22, 'l');
    map_insert(mapVI, 23, 'i');
    map_insert(mapVI, 24, 'c');
    map_insert(mapVI, 25, 't');
    map_insert(mapVI, 26, 'w');

    // VII
    std::map<int, int> mapVII{};
    map_insert(mapVII, 1,  'n');
    map_insert(mapVII, 2,  'z');
    map_insert(mapVII, 3,  'j');
    map_insert(mapVII, 4,  'h');
    map_insert(mapVII, 5,  'g');
    map_insert(mapVII, 6,  'r');
    map_insert(mapVII, 7,  'c');
    map_insert(mapVII, 8,  'x');
    map_insert(mapVII, 9,  'm');
    map_insert(mapVII, 10, 'y');
    map_insert(mapVII, 11, 's');
    map_insert(mapVII, 12, 'w');
    map_insert(mapVII, 13, 'b');
    map_insert(mapVII, 14, 'o');
    map_insert(mapVII, 15, 'u');
    map_insert(mapVII, 16, 'f');
    map_insert(mapVII, 17, 'a');
    map_insert(mapVII, 18, 'i');
    map_insert(mapVII, 19, 'v');
    map_insert(mapVII, 20, 'l');
    map_insert(mapVII, 21, 'p');
    map_insert(mapVII, 22, 'e');
    map_insert(mapVII, 23, 'k');
    map_insert(mapVII, 24, 'q');
    map_insert(mapVII, 25, 'd');
    map_insert(mapVII, 26, 't');

    // VIII
    std::map<int, int> mapVIII{};
    map_insert(mapVIII, 1,  'f');
    map_insert(mapVIII, 2,  'k');
    map_insert(mapVIII, 3,  'q');
    map_insert(mapVIII, 4,  'h');
    map_insert(mapVIII, 5,  't');
    map_insert(mapVIII, 6,  'l');
    map_insert(mapVIII, 7,  'x');
    map_insert(mapVIII, 8,  'o');
    map_insert(mapVIII, 9,  'c');
    map_insert(mapVIII, 10, 'b');
    map_insert(mapVIII, 11, 'j');
    map_insert(mapVIII, 12, 's');
    map_insert(mapVIII, 13, 'p');
    map_insert(mapVIII, 14, 'd');
    map_insert(mapVIII, 15, 'z');
    map_insert(mapVIII, 16, 'r');
    map_insert(mapVIII, 17, 'a');
    map_insert(mapVIII, 18, 'm');
    map_insert(mapVIII, 19, 'e');
    map_insert(mapVIII, 20, 'w');
    map_insert(mapVIII, 21, 'n');
    map_insert(mapVIII, 22, 'i');
    map_insert(mapVIII, 23, 'u');
    map_insert(mapVIII, 24, 'y');
    map_insert(mapVIII, 25, 'g');
    map_insert(mapVIII, 26, 'v');

    init = true;
    return new std::map<int, int>[]{mapI, mapII, mapIII, mapIV, mapV, mapVI, mapVII, mapVIII};
}
