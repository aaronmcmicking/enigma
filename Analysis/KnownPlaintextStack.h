//
// Created by aaron on 2023-06-19.
//

#ifndef ENIGMA_KNOWNPLAINTEXTSTACK_H
#define ENIGMA_KNOWNPLAINTEXTSTACK_H


#include <stack>
#include <vector>
#include "../Enigma/Headers/EnigmaMachine.h"

/*
 * Poorly implemented known-plaintext attack.
 *
 * Extrememly slow and will likely be deleted (hence barren documentation)
 */
class KnownPlaintextStack {
public:
    static int main();

    static void decrypt(const char* text, long size, const char* plaintext, long plaintext_size,
                            EnigmaConfig& best_config);
private:
//    static std::stack<EnigmaConfig> config_stack;

    static bool strneq(const char* str1, const char* str2, int n); // returns true if str1==str2 for first n chars

    static void generate_plugboard_pair_permutations(std::vector<char*> &permutations);

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);
};


#endif //ENIGMA_KNOWNPLAINTEXTSTACK_H
