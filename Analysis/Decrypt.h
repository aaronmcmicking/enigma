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

    typedef struct{
        int* rotors;
        int* rotor_pos;
        char reflector;
        Method analysis_method;
        long double fitness;
    }RotorDecryptInfo;

    static void find_rotors(EnigmaMachine em, Method method, char* e_text, long text_size, std::list<RotorDecryptInfo>& best_rotors);

    static void find_rings(EnigmaMachine em, Method method, const char* text, std::vector<std::vector<int>>& best_ring_settings);

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);

    static std::string itor(int i); // int to roman numeral

    static void print_rotor_decrypt_info_list(std::list<RotorDecryptInfo>& info);

};


#endif //ENIGMA_DECRYPT_H
