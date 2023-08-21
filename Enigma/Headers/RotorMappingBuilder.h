//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORMAPPINGBUILDER_H
#define ENIGMA_ROTORMAPPINGBUILDER_H

#include "Rotor.h"
#include <string>

/*
 * Stores and provides hardcoded values for the conversion maps used in Rotors.
 *
 * These processes are seperated from Rotor.h to avoid clutter.
 */
class RotorMappingBuilder {
public:
    static bool init; // true if the maps still need to be generated, false otherwise
    static int** rotor_mappings; // the constructor rotor mappings

    // returns the conversion map for the specified rotor. 1 <= rotor_number <= 8
    static int* get_rotor_mapping(int rotor_number);

//    static void set_init(bool state);

    // sets rotor_mappings to nullptr
    static void nullify_mappings();

private:

    /* Fills an array map with the corresponding conversions from `vals`.
     * `vals` has format "PQLAWOKSEIJDRUHFYTGZMXNCBV" with each character in order corrosponding on that rotor to
     * "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (in this example, A->P, B->Q, Z->V, etc).
     */
    static void map_fill(int map[CONVERSION_MAP_ARRAY_SIZE], std::string vals);

    // Generates the mappings for all eight rotors and returns an array containing them
    static int** construct_rotor_mappings();

};

#endif //ENIGMA_ROTORMAPPINGBUILDER_H
