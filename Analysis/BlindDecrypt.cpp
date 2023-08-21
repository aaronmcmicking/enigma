//
// Created by aaron on 2023-06-06.
//

#include <iostream>
#include "BlindDecrypt.h"
#include "IndexOfCoincidence/IndexOfCoincidence.h"
#include "CharacterFrequency/CharacterFrequency.h"
#include "stdo.h"
#include <cmath>
#include <iomanip>
#include <chrono>

template<class DecryptInfo>
void BlindDecrypt::print_decrypt_info_list(const std::list<DecryptInfo>& list){
    bool first {true};
    for(const auto& info: list){
        info.print(first);
        first = false;
    }
}

double BlindDecrypt::calculate_fitness(stdo::Method method, char *text, int text_size,
                                       const std::string& current_target) {
    using namespace stdo;
    switch(method){
        case INDEX_OF_COINCIDENCE:
            return static_cast<double>(IndexOfCoincidence::calculate(text, text_size));
        case CHARACTER_FREQUENCY:
            return CharacterFrequency::calculate(text, text_size);
        case KNOWN_PLAINTEXT_SIMPLE:
            std::cout << "KNOWN_PLAINTEXT_SIMPLE fitness calculation not currently supported by DecryptInfo.cpp" << std::endl;
            return -1.0;
        default:
            std::cout << "no decryption method selected for " << current_target << std::endl;
            return -1.0;
    }
}

void BlindDecrypt::generate_rotor_permutations(std::vector<std::vector<int>>& permutations) {
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

void BlindDecrypt::generate_plugboard_pair_permutations(std::vector<char*> &permutations) {
    permutations.clear();
    for (char c1 {'A'}; c1 <= 'Z'; c1++) {
        for(char c2 {static_cast<char>(c1+1)}; c2 <= 'Z'; c2++){
            char* n = new char[]{c1, c2};
            permutations.push_back(n);
        }
    }
    char* n = new char[2]{' ', ' '}; // no plug is always an option
    permutations.push_back(n);
}

void BlindDecrypt::find_rotors(stdo::Method method, const char* e_text, long text_size,
                               std::list<RotorDecryptInfo>& best_rotors) {
    std::vector<std::vector<int>> rotor_positions {};
    generate_rotor_permutations(rotor_positions);

    EnigmaConfig config {};
    EnigmaMachine em {config};

    em.set_ring_pos(new int[]{13, 13, 13});

    if(!best_rotors.empty()){
        best_rotors.clear();
    }

    char* d_text = new char[text_size+1]{0};

    long double cur_fitness;
    long double best_fitness {};

    for(std::vector<int> cur_rotors: rotor_positions){
//        auto start_time {std::chrono::high_resolution_clock::now()};
        for(int r3_p {1}; r3_p <= 26; r3_p++){
            stdo::arrcpy3(config.rotors, cur_rotors[0], cur_rotors[1], cur_rotors[2]);
            for(int r2_p {1}; r2_p <= 26; r2_p++){
                for(int r1_p {1}; r1_p <= 26; r1_p++){
                    for(char ref {'a'}; ref <= 'c'; ref++){
                        // print the current rotor configuration
                        if(r1_p == 1 && r2_p == 1 && r3_p == 1 && ref == 'a') {
                            using namespace std;
                            cout << left << setw(4) << stdo::itor(cur_rotors[0]) << " "
                                 << left << setw(4) << stdo::itor(cur_rotors[1]) << " "
                                 << left << setw(4) << stdo::itor(cur_rotors[2]) << endl;
                        }

                        // set new rotor settings
                        stdo::arrcpy3(config.rotor_pos, r1_p, r2_p, r3_p);
                        config.reflector = ref;

                        em.set_config(config);

                        // decrypt
                        em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                        // analyze
                        cur_fitness = calculate_fitness(method, d_text, text_size, "rotor settings");

                        // if a good rotor configuration was found, store it
                        if(best_rotors.empty() || cur_fitness >= best_rotors.back().fitness){
                            RotorDecryptInfo ninfo{
                                    new int[3]{cur_rotors[0], cur_rotors[1], cur_rotors[2]},
                                    new int[3]{r1_p, r2_p, r3_p},
                                    ref,
                                    method,
                                    cur_fitness
                            };

                            if(best_rotors.size() >= 10) best_rotors.pop_back();
                            best_rotors.push_back(ninfo);
                            best_rotors.sort(DecryptInfo::strict_weak_ordering);

                            // if this is the best rotor configuration so far, write it's associated decryption to disk
                            if(cur_fitness > best_fitness) {
//                                std::cout << "new best fitness: " << best_fitness << std::endl;
                                best_fitness = cur_fitness;
                                std::ofstream ofile{BlindDecrypt::textfiles_path + "decrypted_rotors.txt"};
                                ofile << d_text;
                                ofile.close();
                            }
                        } // should add settings to best_rotors

                    } // ref
                } // r3_p
            } // r2_p
        } // r1_p
//        auto dur {duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time)};
//        std::cout << "perm took " << dur.count() << "ms" << std::endl;
    } // rotor perms

    delete[] d_text;
}

void BlindDecrypt::find_rings(stdo::Method method, const char *e_text, long text_size,
                              const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings){

    EnigmaMachine em {new int[3] {1, 2, 3}, new int[3] {1, 1, 1}, new int[3] {0, 0, 0}, 'a', ""};

    EnigmaConfig config {};

    char* d_text {new char[text_size+1]{0}};

    long double cur_fitness {};
    long double best_fitness {};

    auto rotor_it {best_rotors.cbegin()};
    for(int i {0}; i < 5; i++){
        auto cur_rotor_info {rotor_it};
        rotor_it++;
        config = cur_rotor_info->to_config();
        for (int r1{1}; r1 <= 26; r1++) {
            for (int r2{1}; r2 <= 26; r2++) {
                stdo::arrcpy3(config.ring_pos, r1, r2, 1);

                    em.set_config(config);

                    em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                    cur_fitness = calculate_fitness(method, d_text, text_size, "ring settings");

                    if(best_rings.empty() || cur_fitness >= best_rings.back().fitness){
                        RingDecryptInfo ninfo{
                            *cur_rotor_info,
                            new int[3]{r1, r2, 1},
                            method,
                            cur_fitness
                        };

                        if(best_rings.size() >= 5) best_rings.pop_back();
                        best_rings.push_back(ninfo);
                        best_rings.sort(DecryptInfo::strict_weak_ordering);

                        // if this is the best rotor configuration so far, write it's associated decryption to disk
                        if(cur_fitness > best_fitness || best_rings.empty()) {
//                            std::cout << "new best fitness: " << best_fitness << std::endl;
                            best_fitness = cur_fitness;
                            std::ofstream ofile{BlindDecrypt::textfiles_path + "decrypted_rings.txt"};
                            ofile << d_text;
                            ofile.close();
                        }
                    } // should add to best settings

            } // r2
        } // r1
    } // best rotor positions

    delete[] d_text;
}

void BlindDecrypt::find_plugs(stdo::Method method, const char *e_text, long text_size,
                              const RingDecryptInfo& best_ring, PlugboardDecryptInfo& best_plugboard) {

    EnigmaConfig config {best_ring.to_config()};

    EnigmaMachine em {config};

    std::vector<char*> possible_pairs {};
    generate_plugboard_pair_permutations(possible_pairs);

    char* d_text = new char[text_size+1]{0};

    double best_fitness_on_cycle {};
    char* best_pair_on_cycle {new char[3]{}};
    double cur_fitness;
    std::string fixed {};

    for(int i {}; i < 10; i++) { // loop 10 times for max 10 pairs for a given Enigma configuration
        for (char *pair: possible_pairs) {

            char cur[]{pair[0], pair[1], '\0'};
            if(!Plugboard::can_add(cur, fixed)){
                continue;
            }

            em.set_config(config);
            std::string set_str {fixed + " " + cur};
            em.set_plugboard_settings(set_str);
            em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

            cur_fitness = calculate_fitness(method, d_text, text_size, "plugboard");

            if (cur_fitness > best_fitness_on_cycle) {
                best_fitness_on_cycle = cur_fitness;
                stdo::arrncpy(best_pair_on_cycle, cur, 3);
            }

            if(possible_pairs.back()[0] == pair[0] && possible_pairs.back()[1] == pair[1]){
                fixed += " ";
                fixed += best_pair_on_cycle;
                best_fitness_on_cycle = 0;
            } // fixing pair
        } // for all pairs
    } // x10 for max 10 pairs

    config.plugboard = fixed;
    em.set_config(config);
    em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);
    double final_fitness = calculate_fitness(method, d_text, text_size, "plugboard");

    std::ofstream ofile{BlindDecrypt::textfiles_path + "decrypted_plugs.txt"};
    ofile << d_text;
    ofile.close();

    best_plugboard = *(new PlugboardDecryptInfo {
        best_ring,
        fixed,
        method,
        final_fitness
    });

    delete[] d_text;
}


void BlindDecrypt::decrypt(const std::string &input_filepath, const std::string &output_filepath) {
    int e_size {};
    char* e_text = stdo::load_from_file(input_filepath, &e_size);


    auto start_time {std::chrono::high_resolution_clock::now()};

    std::list<RotorDecryptInfo> best_rotors {};
    find_rotors(stdo::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    std::cout << std::endl;
    print_decrypt_info_list(best_rotors);
    std::cout << std::endl;

    std::list<RingDecryptInfo> best_rings {};
    find_rings(stdo::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors, best_rings);
    print_decrypt_info_list(best_rings);
    std::cout << std::endl;

    PlugboardDecryptInfo best_plugboard{};
    find_plugs(stdo::INDEX_OF_COINCIDENCE, e_text, e_size, best_rings.front(), best_plugboard);
    std::cout << "FINAL SETTINGS:" << std::endl;
    best_plugboard.print(true);

    auto end_time {std::chrono::high_resolution_clock::now()};
    auto duration {duration_cast<std::chrono::milliseconds>(end_time - start_time)};
    if(duration.count() > 10000){
        std::cout << "decryption took " << duration.count() / 1000 << " seconds" << std::endl;
    }else {
        std::cout << "decryption took " << duration.count() << " milliseconds" << std::endl;
    }

    EnigmaMachine em {best_plugboard.to_config()};
    em.encrypt_or_decrypt_file(input_filepath, output_filepath);

    delete e_text;
}

int BlindDecrypt::main(){

    int init_rotors[]{2, 5, 3};
    int init_rotor_pos[]{21, 19, 6};
    int init_rings[]{17, 25, 1};
    EnigmaConfig encrypt_config {
            init_rotors,
            init_rotor_pos,
            init_rings,
            'B',
            "JM HO PQ LD UG ZF KS AN BX YW"
//            "QU IN VB LE CO KR WP ZH AS TY"
//            "QU IN VB LE"
//            "IK BH RG NA PF"
//            "AF",
//            ""
    };

    EnigmaMachine em {encrypt_config};


    const std::string plaintext_path {BlindDecrypt::textfiles_path + "plaintext.txt"};
    const std::string encrypted_path {BlindDecrypt::textfiles_path + "encrypted.txt"};
    const std::string decrypted_path {BlindDecrypt::textfiles_path + "decrypted.txt"};
    stdo::format_input_file(plaintext_path);
    em.encrypt_or_decrypt_file(plaintext_path, encrypted_path);

    decrypt(encrypted_path, decrypted_path);

    std::cout << std::endl << "Done" << std::endl;
    return 0;
}
