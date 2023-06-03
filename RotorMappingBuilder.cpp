//
// Created by aaron on 2023-06-01.
//

#include <iostream>
#include <cctype>
#include <string>
#include "RotorMappingBuilder.h"
#include "Operations.h"

bool RotorMappingBuilder::init {false};
int** RotorMappingBuilder::rotor_mappings {nullptr};

int* RotorMappingBuilder::get_rotor_mapping(int rotor_number){
    if(!init){
        rotor_mappings = construct_rotor_mappings();
    }
    if(rotor_mappings == nullptr) {
        std::cout << "rotor_mappings == null" << std::endl;
        throw std::exception{}; }
    return rotor_mappings[rotor_number - 1];
}

void RotorMappingBuilder::set_init(bool state){
    init = state;
}

// sets the rotor_mappings to null
void RotorMappingBuilder::nullify_mappings(){
    rotor_mappings = nullptr;
}

void RotorMappingBuilder::map_fill(int* map, std::string values){
    for(int i {Rotor::min_position}; i <= Rotor::max_position; i++){
        map[i] = Operations::ctoi(static_cast<char>(tolower(values.at(i-1))));
    }
}

int** RotorMappingBuilder::construct_rotor_mappings() {
    // I
    static int mapI[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapI_con {"EKMFLGDQVZNTOWYHXUSPAIBRCJ"};
    map_fill(mapI, mapI_con);

    // II
    static int mapII[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapII_con {"AJDKSIRUXBLHWTMCQGZNPYFVOE"};
    map_fill(mapII, mapII_con);

    // III
    static int mapIII[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapIII_con {"BDFHJLCPRTXVZNYEIWGAKMUSQO"};
    map_fill(mapIII, mapIII_con);

    // IV
    static int mapIV[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapIV_con {"ESOVPZJAYQUIRHXLNFTGKDCMWB"};
    map_fill(mapIV, mapIV_con);

    // V
    static int mapV[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapV_con {"VZBRGITYUPSDNHLXAWMJQOFECK"};
    map_fill(mapV, mapV_con);

    // VI
    static int mapVI[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapVI_con {"JPGVOUMFYQBENHZRDKASXLICTW"};
    map_fill(mapVI, mapVI_con);

    // VII
    static int mapVII[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapVII_con {"NZJHGRCXMYSWBOUFAIVLPEKQDT"};
    map_fill(mapVII, mapVII_con);

    // VIII
    static int mapVIII[CONVERSION_MAP_ARRAY_SIZE] {};
    std::string mapVIII_con {"FKQHTLXOCBJSPDZRAMEWNIUYGV"};
    map_fill(mapVIII, mapVIII_con);

    init = true;
    return new int*[]{mapI, mapII, mapIII, mapIV, mapV, mapVI, mapVII, mapVIII};
}
