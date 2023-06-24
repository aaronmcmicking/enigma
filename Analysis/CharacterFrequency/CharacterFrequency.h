//
// Created by aaron on 2023-06-10.
//

#ifndef ENIGMA_CHARACTERFREQUENCY_H
#define ENIGMA_CHARACTERFREQUENCY_H

#include "../Op.h"

/*
 * Character Frequency is a cryptographic fitness function that quantifies how similar a block of text is to actual
 * language text. For more information see https://en.wikipedia.org/wiki/frequency_analysis and
 * https://en.wikipedia.org/wiki/letter_frequency.
 */
class CharacterFrequency {
public:
    // the expected frequency for all letters A-Z
    // english letter frequencies sourced from https://www3.nd.edu/~busiforc/handouts/cryptography/letterfrequencies.html
    constexpr static const double expected[27] {0.00,
                                                0.084966,
                                                0.02072,
                                                0.045388,
                                                0.033844,
                                                0.0111607,
                                                0.011821,
                                                0.024705,
                                                0.030034,
                                                0.075448,
                                                0.001965,
                                                0.011016,
                                                0.054893,
                                                0.030129,
                                                0.066544,
                                                0.071635,
                                                0.031671,
                                                0.001962,
                                                0.075809,
                                                0.057351,
                                                0.069509,
                                                0.036308,
                                                0.010074,
                                                0.012899,
                                                0.002902,
                                                0.017779,
                                                0.002722
                                                };

    /*
     * Calculates 1 - the sum of the differences between the measured and expected frequency of each letter
     * (ie. higher fitness == better fitness)
     */
    static double calculate(const char* text, int size);
};


#endif //ENIGMA_CHARACTERFREQUENCY_H
