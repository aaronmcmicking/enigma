//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_BLINDDECRYPT_H
#define ENIGMA_BLINDDECRYPT_H

#include <vector>
#include <list>
#include <queue>
#include <utility>
#include "../Enigma/Headers/EnigmaMachine.h"


class BlindDecrypt {
public:
    enum Method{
        INDEX_OF_COINCIDENCE
    };

    typedef struct{
        int* rotors;
        int* rotor_pos;
        char reflector;
        Method method;
        long double fitness;
    }RotorDecryptInfo;

    typedef struct{
        RotorDecryptInfo rotor_info;
        int* rings;
        Method method;
        long double fitness;
    }RingDecryptInfo;

    static void find_rotors(EnigmaMachine em, Method method, const char* e_text, long text_size, std::list<RotorDecryptInfo>& best_rotors);

    static void find_reflector(EnigmaMachine em, Method method, const char* e_text, long text_size, std::list<RotorDecryptInfo>& best_rotors);

    static void find_rings(EnigmaMachine em, BlindDecrypt::Method method, const char *e_text, long text_size,
                           const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings);

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);

    static std::string itor(int i); // int to roman numeral

    static void print_rotor_decrypt_info_list(const std::list<RotorDecryptInfo>& info);

    static void print_ring_decrypt_info_list(const std::list<RingDecryptInfo>& info);
};


#endif //ENIGMA_BLINDDECRYPT_H
