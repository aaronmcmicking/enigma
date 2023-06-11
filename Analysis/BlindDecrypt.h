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
        INDEX_OF_COINCIDENCE,
        CHARACTER_FREQUENCY
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
        int* ring_pos;
        Method method;
        long double fitness;
    }RingDecryptInfo;

    typedef struct{
        std::string plugboard;
        RingDecryptInfo ring_info;
        Method method;
        long double fitness;
    }PlugboardDecryptInfo;

    static void print_rotor_decrypt_info_list(const std::list<RotorDecryptInfo>& info);

    static void print_ring_decrypt_info_list(const std::list<RingDecryptInfo>& info);

    static void print_plugboard_decrypt_info_list(const std::list<PlugboardDecryptInfo> &info);

    static void find_rotors(EnigmaMachine em, Method method, const char* e_text, long text_size, std::list<RotorDecryptInfo>& best_rotors);

    static void find_rings(EnigmaMachine em, BlindDecrypt::Method method, const char *e_text, long text_size,
                           const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings);

    static void find_plugs(EnigmaMachine em, BlindDecrypt::Method method, const char* e_text, long text_size,
                           const std::list<RingDecryptInfo>& best_rings, std::list<PlugboardDecryptInfo>& best_plugboards);

    static std::string itor(int i); // int to roman numeral

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);

    static void generate_plugboard_pair_permutations(std::vector<char*>& permutations);

private:
    static double calculate_fitness(Method method, char* text, int text_size, const std::string& current_target);
};


#endif //ENIGMA_BLINDDECRYPT_H
