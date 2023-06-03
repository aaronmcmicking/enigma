//
// Created by aaron on 2023-06-01.
//

#include <map>
#include <cctype>
#include <string>
#include "RotorMappingBuilder.h"
#include "Operations.h"

bool RotorMappingBuilder::init {false};
std::map<int, int>* RotorMappingBuilder::rotor_mappings {};

std::map<int, int> RotorMappingBuilder::get_rotor_mapping(int rotor_number){
    if(!init){
        rotor_mappings = construct_rotor_mappings();
    }
    if(rotor_mappings == nullptr) throw std::exception{};
    return rotor_mappings[rotor_number - 1];
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
    map.insert(pair(k, Operations::ctoi(v)));
}

std::map<int, int> RotorMappingBuilder::get_reflector_mapping(char which) {
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

    map_fill(map, reflection);

//    for(int i {1}; i <= 26; i++){
//        map_insert(map, i, static_cast<char>(tolower(reflection[i-1])));
//    }

    return map;
}

void RotorMappingBuilder::map_fill(std::map<int, int> &map, std::string vals) {
    for(int i = 1; i <= 26; i++){
        map_insert(map, i, static_cast<char>(tolower(vals.at(i-1))));
    }
}

std::map<int, int>* RotorMappingBuilder::construct_rotor_mappings() {
    // I
    std::map<int, int> mapI{};
    std::string mapI_con {"EKMFLGDQVZNTOWYHXUSPAIBRCJ"};
    map_fill(mapI, mapI_con);

    // II
    std::map<int, int> mapII{};
    std::string mapII_con {"AJDKSIRUXBLHWTMCQGZNPYFVOE"};
    map_fill(mapII, mapII_con);

    // III
    std::map<int, int> mapIII{};
    std::string mapIII_con {"BDFHJLCPRTXVZNYEIWGAKMUSQO"};
    map_fill(mapIII, mapIII_con);

    // IV
    std::map<int, int> mapIV{};
    std::string mapIV_con {"ESOVPZJAYQUIRHXLNFTGKDCMWB"};
    map_fill(mapIV, mapIV_con);

    // V
    std::map<int, int> mapV{};
    std::string mapV_con {"VZBRGITYUPSDNHLXAWMJQOFECK"};
    map_fill(mapV, mapV_con);

    // VI
    std::map<int, int> mapVI{};
    std::string mapVI_con {"JPGVOUMFYQBENHZRDKASXLICTW"};
    map_fill(mapVI, mapVI_con);

    // VII
    std::map<int, int> mapVII{};
    std::string mapVII_con {"NZJHGRCXMYSWBOUFAIVLPEKQDT"};
    map_fill(mapVII, mapVII_con);

    // VIII
    std::map<int, int> mapVIII{};
    std::string mapVIII_con {"FKQHTLXOCBJSPDZRAMEWNIUYGV"};
    map_fill(mapVIII, mapVIII_con);

    init = true;
    return new std::map<int, int>[]{mapI, mapII, mapIII, mapIV, mapV, mapVI, mapVII, mapVIII};
}
