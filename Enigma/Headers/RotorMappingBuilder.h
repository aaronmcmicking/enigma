//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORMAPPINGBUILDER_H
#define ENIGMA_ROTORMAPPINGBUILDER_H


#include "Rotor.h"

class RotorMappingBuilder {
public:
    static bool init;
    static int** rotor_mappings;

    static int* get_rotor_mapping(int rotor_number);

    static void set_init(bool state);

    static void nullify_mappings();

private:

    static void map_fill(int map[CONVERSION_MAP_ARRAY_SIZE], std::string vals);

    static int** construct_rotor_mappings();

};

#endif //ENIGMA_ROTORMAPPINGBUILDER_H
