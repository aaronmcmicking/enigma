//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_BLINDDECRYPT_H
#define ENIGMA_BLINDDECRYPT_H

#include "DecryptionReturnables/RotorDecryptInfo.h"
#include "DecryptionReturnables/RingDecryptInfo.h"
#include "DecryptionReturnables/PlugboardDecryptInfo.h"
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
    static int main(); // mostly used for testing, sort of shadows main.cpp (also is called from main.cpp::main())

    static void decrypt(const std::string& input_filepath, const std::string& output_filepath);

    template<class DecryptInfo>
    static void print_decrypt_info_list(const std::list<DecryptInfo>& list);

    static void find_rotors(Op::Method method, const char* e_text, long text_size, std::list<RotorDecryptInfo>& best_rotors);

    static void find_rings(Op::Method method, const char *e_text, long text_size,
                           const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings);

    static void find_plugs(Op::Method method, const char* e_text, long text_size,
                           const RingDecryptInfo& best_ring, PlugboardDecryptInfo& best_plugboard);

    static void generate_rotor_permutations(std::vector<std::vector<int>>& permutations);

    static void generate_plugboard_pair_permutations(std::vector<char*>& permutations);

private:
    static double calculate_fitness(Op::Method method, char* text, int text_size, const std::string& current_target);
};


#endif //ENIGMA_BLINDDECRYPT_H
