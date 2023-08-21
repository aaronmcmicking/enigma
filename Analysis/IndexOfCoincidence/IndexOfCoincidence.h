//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_INDEXOFCOINCIDENCE_H
#define ENIGMA_INDEXOFCOINCIDENCE_H

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

#include <string>
#include "../stdo.h"

/*
 * Index of Coincidence is a cryptographic fitness function that quantifies how similar a block of text is to actual
 * language text. For more information see https://en.wikipedia.org/wiki/index_of_coincidence.
 *
 * In short, IOC quantifies the likelihood that two characters selected randomly from the text will be the same character.
 * Completely random text has an IOC of ~1.00 and standard English text has an IOC of ~1.73
 */
class IndexOfCoincidence {
public:
    constexpr static long double ENGLISH_EXPECTED_IOC {1.73}; // the expected index of coincidence for English text

    // Normalizing coefficient is used to reformat an IOC in terms of the number of characters in an alphabet.
    // See https://en.wikipedia.org/wiki/Index_of_coincidence#calculation for more information.
    static const int NORMALIZING_COEFFICIENT {26};

    /*
     * Calculates IOC of text in a given char array.
     * Returns 1 - abs( expected_ioc - measured_ioc )
     * (ie. higher fitness == better fitness)
     */
    static long double calculate(const char* text, int size);

    /*
     * Calculates IOC of text in a given file.
     */
    static long double calculate_from_file(const std::string& filename);
};


#endif //ENIGMA_INDEXOFCOINCIDENCE_H
