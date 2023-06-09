//
// Created by aaron on 2023-06-06.
//

#include <iostream>
#include "Decrypt.h"
#include "IndexOfCoincidence/IndexOfCoincidence.h"
#include <cmath>
#include <iomanip>

/**
 * Defines weak ordering for lists of Decrypt::RotorDecryptInfo structs. An item should come first in a list if
 * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
 * @param first The first item to compare.
 * @param second The second item to compare.
 * @return True if `first` is ordered before `second`, false otherwise.
 */
bool rotor_decrypt_info_sort_order(const Decrypt::RotorDecryptInfo& first, const Decrypt::RotorDecryptInfo& second){
    return first.fitness >= second.fitness;
}

void Decrypt::print_rotor_decrypt_info_list(std::list<RotorDecryptInfo>& info) {
    for(auto& r: info){
        std::cout << std::setw(3) << Decrypt::itor(r.rotors[0]) << "  " << std::setw(2) << r.rotor_pos[0] << " |   "
                  << std::setw(3) << Decrypt::itor(r.rotors[1]) << "  " << std::setw(2) << r.rotor_pos[1] << " |   "
                  << std::setw(3) << Decrypt::itor(r.rotors[2]) << "  " << std::setw(2) << r.rotor_pos[2] << " |   "
                  << "REF: " << static_cast<char>(toupper(r.reflector)) << "  "
                  << " -> " << r.fitness << std::endl;
    }
}

void Decrypt::generate_rotor_permutations(std::vector<std::vector<int>>& permutations) {
    for(int i {1}; i <= 5; i++){
        for(int j {1}; j <= 5; j++){
            for(int w {1}; w <= 5; w++){
                if(i != j && i != w && j != w){ // get unique arrangements only
                    auto* n = new std::vector<int>{i, j, w};
                    permutations.push_back(*n);
                }
            }
        }
    }
}

std::string Decrypt::itor(int i){
    if(!EMOps::is_in_range(i, 1, 8)){
        return "INVALID NUMERAL";
    }
    std::string str[] {"I", "II ", "III", "IV", "V", "VI", "VII", "VIII"};
    return str[i-1];
}

void Decrypt::find_rotors(EnigmaMachine em, Decrypt::Method method, char* e_text, long text_size,
                          std::list<RotorDecryptInfo>& best_rotors) {
    std::vector<std::vector<int>> rotor_perms {};
    generate_rotor_permutations(rotor_perms);

    EnigmaConfig config {
        .rotors {1, 2, 3},
        .rotor_pos{1, 1, 1},
        .ring_pos{0, 0, 0},
        .reflector = 'a',
        .plugboard {""}
    };

    EnigmaConfig best_config {};

    if(!best_rotors.empty()){
        best_rotors.clear();
    }

    char* d_text = new char[text_size+1]{0};

    long double cur_fitness {};
    long double best_fitness {};

    for(std::vector<int> cur_rotors: rotor_perms){
        for(int r1_p {1}; r1_p <= 26; r1_p++){
            Ops::rep_arr3(config.rotors, cur_rotors[0], cur_rotors[1], cur_rotors[2]);
            for(int r2_p {1}; r2_p <= 26; r2_p++){
                for(int r3_p {1}; r3_p <= 26; r3_p++){
                    for(char ref {'a'}; ref <= 'c'; ref++){
                        // print the current rotar configuration
                        if(r1_p == 1 && r2_p == 1 && r3_p == 1 && ref == 'a') {
                                std::cout   << std::setw(3) << itor(cur_rotors[0]) << " "
                                            << std::setw(3) << itor(cur_rotors[1]) << " "
                                            << std::setw(3) << itor(cur_rotors[2]) << std::endl;
                        }

                        // set new rotor settings
                        Ops::rep_arr3(config.rotor_pos, r1_p, r2_p, r3_p);
                        config.reflector = ref;
                        em.set_config(config);

                        // decrypt
                        em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                        // analyze
                        switch (method) {
                            case (Method::INDEX_OF_COINCIDENCE):
                                cur_fitness = IndexOfCoincidence::calculate(d_text, text_size);
//                                for(int i {0}; i < 10; i++) std::cout << d_text[i];
                                break;
                            default:
                                std::cout << "decrypt: no method selected" << std::endl;
                                return;
                        }

                        // if a good rotor configuration was found, store it
                        if(best_rotors.empty() || cur_fitness >= best_rotors.back().fitness){
                            int* r = new int[3]{cur_rotors[0], cur_rotors[1], cur_rotors[2]};
                            int* rp = new int[3]{r1_p, r2_p, r3_p};

                            RotorDecryptInfo* ninfo{new RotorDecryptInfo {
                                                            .rotors = r,
                                                            .rotor_pos = rp,
                                                            .reflector = ref,
                                                            .analysis_method = method,
                                                            .fitness = cur_fitness
                                                    }};

                            if(best_rotors.size() >= 10) best_rotors.pop_back();
                            best_rotors.push_back(*ninfo);
                            best_rotors.sort(rotor_decrypt_info_sort_order);

                            // if this is the best rotor configuration so far, write it's associated decryption to disk
                            if(cur_fitness > best_fitness) {
                                std::cout << "new best fitness: " << best_fitness << std::endl;
                                best_fitness = cur_fitness;
                                std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted.txt)"};
                                ofile << d_text;
                                ofile.close();
                            }
                        } // should add settings to best_rotors

                    } // ref
                } // r3_p
            } // r2_p
        } // r1_p
    } // rotor perms

    delete[] d_text;
}

void Decrypt::find_rings(EnigmaMachine em, Decrypt::Method method, const char *text,
                         std::vector<std::vector<int>> &best_ring_settings) {
    (void) em;
    (void) method;
    (void) text;
    (void) best_ring_settings;
}

int main(){
    EnigmaConfig config {
            .rotors {5, 3, 4},
            .rotor_pos{25, 7, 7},
//            .ring_pos{9, 22, 17},
            .ring_pos{0, 0, 0},
            .reflector ='C',
            .plugboard {""}
            //.plugboard {"QP AL ZM XK SN DJ CH FB GU TY"}
    };

    EnigmaMachine em {config};

    em.encrypt_or_decrypt_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)", R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)");

    int e_size {};
    char* e_text = Ops::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", &e_size);

    std::list<Decrypt::RotorDecryptInfo> best_rotors {};

    Decrypt::find_rotors(em, Decrypt::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    std::cout << std::endl;
    Decrypt::print_rotor_decrypt_info_list(best_rotors);

    delete e_text;
    std::cout << std::endl << "Done" << std::endl;
    return 0;
}