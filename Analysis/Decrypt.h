//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_DECRYPT_H
#define ENIGMA_DECRYPT_H

#include <vector>
#include <list>
#include <queue>
#include <utility>
#include "../Enigma/Headers/EnigmaMachine.h"

class Decrypt {
public:
    enum Method{
        INDEX_OF_COINCIDENCE
    };

    static void decrypt(Method method);

    // best settings has pairs<rotors, rotor_pos>
    static void find_rotors(EnigmaMachine em, Method method, char* e_text, long text_size, std::list<std::pair<std::pair<int *, int *>, long double>>& best_rotors);

    static void find_rings(EnigmaMachine em, Method method, const char* text, std::vector<std::vector<int>>& best_ring_settings);

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);

    static std::string itor(int i); // int to roman numeral

};


#endif //ENIGMA_DECRYPT_H
