//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_REFLECTOR_H
#define ENIGMA_REFLECTOR_H


#include "stdeo.h"
#include "Rotor.h"

/*
 * See https://en.wikipedia.org/wiki/Enigma_machine for more information.
 *
 * The reflector is placed after the three rotors in the rotor box. It a) converts an input from the 3rd rotor according
 * to a hardcoded mapping, and b) sends its output as input to the rotors in their reverse order
 *
 * Reflector mappings are the same as used in genuine Enigma machines. There are three reflectors implemented, A, B, and
 * C.
 *
 * Similar to rotors and the plugboard, characters are represented in the map as their 1-index position in the English
 * alphabet rather than their integer representation. ie., mapping[1] == 'A', mapping[2] == 'B', etc.
 */
class Reflector {
public:
    // the default is rotor `A`
    Reflector();

    // `c` may be 'A', 'B', or 'C'. Function is case-insensitive.
    explicit Reflector(char c);

    // Sets the current mapping for this reflector according to a reflector code. `c` may be 'A', 'B', or 'C'.
    void set_reflector(char c);

    // Sets the current mapping for this reflector by replacing the current mapping with the one in `r`
    void set_reflector(Reflector r);

    // Converts and input to an output using the current map.
    int reflect(int input);

private:
    // the current mapping used in the reflector
    int* mapping;

    // returns the mapping for a given rotor. `c` may be 'A', 'B', or 'C'. Function is case-insensitive.
    static int* get_mapping(char c);
};


#endif //ENIGMA_REFLECTOR_H
