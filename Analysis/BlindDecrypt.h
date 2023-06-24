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
#include "Op.h"

/*
 * BlindDecrypt employs statistical methods to brute force the Enigma Machine settings used to encrypt given ciphertext.
 */
class BlindDecrypt {
public:
    // used to specify which statistical method should be used during a given decryption process
    enum Method{
        INDEX_OF_COINCIDENCE,
        CHARACTER_FREQUENCY,
        KNOWN_PLAINTEXT_SIMPLE
    };

    // Stores result from rotor decryption
    typedef struct{
        int* rotors;
        int* rotor_pos;
        char reflector;
        Method method;
        long double fitness;
    }RotorDecryptInfo;

    // Stores results from ring position decrypt as well as the rotor decryption information used to attain this info
    typedef struct{
        RotorDecryptInfo rotor_info;
        int* ring_pos;
        Method method;
        long double fitness;
    }RingDecryptInfo;

    // Stores results from plugboard decryption as well as the ring position decryption information used to attain this info
    typedef struct{
        std::string plugboard;
        RingDecryptInfo ring_info;
        Method method;
        long double fitness;
    }PlugboardDecryptInfo;

    static int main(); // mostly used for testing, sort of shadows main.cpp (also is called from main.cpp::main())

    static void decrypt(const std::string& input_filepath, const std::string& output_filepath);

    static void print_rotor_decrypt_info_list(const std::list<RotorDecryptInfo>& info);

    static void print_ring_decrypt_info_list(const std::list<RingDecryptInfo>& info);

    static void print_plugboard_decrypt_info(const PlugboardDecryptInfo& info);

    static void find_rotors(Method method, const char* e_text, long text_size, std::list<RotorDecryptInfo>& best_rotors);

    static void find_rings(BlindDecrypt::Method method, const char *e_text, long text_size,
                           const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings);

    static void find_plugs(BlindDecrypt::Method method, const char* e_text, long text_size,
                           const RingDecryptInfo& best_ring, PlugboardDecryptInfo& best_plugboard);

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);

    static void generate_plugboard_pair_permutations(std::vector<char*>& permutations);

private:
    static double calculate_fitness(Method method, char* text, int text_size, const std::string& current_target);
};


#endif //ENIGMA_BLINDDECRYPT_H
