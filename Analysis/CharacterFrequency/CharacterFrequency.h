//
// Created by aaron on 2023-06-10.
//

#ifndef ENIGMA_CHARACTERFREQUENCY_H
#define ENIGMA_CHARACTERFREQUENCY_H

/*
 * Stores and outputs percentages
 */

class CharacterFrequency {
public:
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

    // returns the (1 - sum of differences between expected percentages and measured percentages)
    // -> returns values >0 and <1
    // ie, the decrypter aims to maximize this
    static double calculate(const char* text, int size);

private:
    static double abs(double val);
};


#endif //ENIGMA_CHARACTERFREQUENCY_H
