//
// Created by aaron on 2023-06-06.
//

#include <iostream>
#include "BlindDecrypt.h"
#include "IndexOfCoincidence/IndexOfCoincidence.h"
#include "CharacterFrequency/CharacterFrequency.h"
#include "KnownPlaintextSimple//KnownPlaintextSimple.h"
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

double BlindDecrypt::calculate_fitness(Op::Method method, char *text, int text_size,
                                     const std::string& current_target) {
    using namespace Op;
    switch(method){
        case INDEX_OF_COINCIDENCE:
            return static_cast<double>(IndexOfCoincidence::calculate(text, text_size));
        case CHARACTER_FREQUENCY:
            return CharacterFrequency::calculate(text, text_size);
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

void BlindDecrypt::find_rotors(Op::Method method, const char* e_text, long text_size,
                               std::list<RotorDecryptInfo>& best_rotors) {
    std::vector<std::vector<int>> rotor_positions {};
    generate_rotor_permutations(rotor_positions);

    EnigmaMachine em {new int[3] {1, 2, 3}, new int[3] {1, 1, 1}, new int[3] {0, 0, 0}, 'a', ""};

    EnigmaConfig config {};

//    EnigmaConfig best_config {};

    if(!best_rotors.empty()){
        best_rotors.clear();
    }

    char* d_text = new char[text_size+1]{0};

    long double cur_fitness;
    long double best_fitness {};

    for(std::vector<int> cur_rotors: rotor_positions){
        for(int r3_p {1}; r3_p <= 26; r3_p++){
            Op::rep_arr3(config.rotors, cur_rotors[0], cur_rotors[1], cur_rotors[2]);
            for(int r2_p {1}; r2_p <= 26; r2_p++){
                for(int r1_p {1}; r1_p <= 26; r1_p++){
                    for(char ref {'a'}; ref <= 'c'; ref++){
                        // print the current rotor configuration
                        if(r1_p == 1 && r2_p == 1 && r3_p == 1 && ref == 'a') {
                            using namespace std;
                            cout << left << setw(4) << Op::itor(cur_rotors[0]) << " "
                                 << left << setw(4) << Op::itor(cur_rotors[1]) << " "
                                 << left << setw(4) << Op::itor(cur_rotors[2]) << endl;
                        }

                        // set new rotor settings
                        Op::rep_arr3(config.rotor_pos, r1_p, r2_p, r3_p);
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
                                std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted_rotors.txt)"};
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

void BlindDecrypt::find_rings(Op::Method method, const char *e_text, long text_size,
                              const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings){

    EnigmaMachine em {new int[3] {1, 2, 3}, new int[3] {1, 1, 1}, new int[3] {0, 0, 0}, 'a', ""};

//    EnigmaConfig config {
//            .rotors {1, 2, 3},
//            .rotor_pos{1, 1, 1},
//            .ring_pos{0, 0, 0},
//            .reflector = 'a',
//            .plugboard {""}
//    };

    EnigmaConfig config {};

    char* d_text {new char[text_size+1]{0}};

    long double cur_fitness {};
    long double best_fitness {};

    auto rotor_it {best_rotors.cbegin()};
    for(int i {0}; i < 5; i++){
        auto rinfo {rotor_it};
        rotor_it++;
        Op::rep_arr3(config.rotors, rinfo->rotors);
        Op::rep_arr3(config.rotor_pos, rinfo->rotor_pos);
        config.reflector = rinfo->reflector;
        for (int r1{1}; r1 <= 26; r1++) {
            for (int r2{1}; r2 <= 26; r2++) {
                    Op::rep_arr3(config.ring_pos, r1, r2, 1);

                    em.set_config(config);

                    em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                    cur_fitness = calculate_fitness(method, d_text, text_size, "ring settings");

                    if(best_rings.empty() || cur_fitness >= best_rings.back().fitness){

                        RingDecryptInfo ninfo{
                            *rinfo,
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
                            std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted_rings.txt)"};
                            ofile << d_text;
                            ofile.close();
                        }
                    } // should add to best settings

            } // r2
        } // r1
    } // best rotor positions

    delete[] d_text;
}

void BlindDecrypt::find_plugs(Op::Method method, const char *e_text, long text_size,
                              const RingDecryptInfo& best_ring, PlugboardDecryptInfo& best_plugboard) {


    EnigmaConfig config {
        best_ring.rotor_info.rotors,
        best_ring.rotor_info.rotor_pos,
        best_ring.ring_pos,
        best_ring.rotor_info.reflector,
        ""
    };

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
                Op::rep_arr(best_pair_on_cycle, cur, 3);
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

    std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted_plugs.txt)"};
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
    char* e_text = Op::load_from_file(input_filepath, &e_size);


    auto start_time {std::chrono::high_resolution_clock ::now()};

    std::list<RotorDecryptInfo> best_rotors {};
    find_rotors(Op::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    std::cout << std::endl;
    print_decrypt_info_list(best_rotors);
    std::cout << std::endl;

    std::list<RingDecryptInfo> best_rings {};
    find_rings(Op::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors, best_rings);
    print_decrypt_info_list(best_rings);
    std::cout << std::endl;

//    auto pst{std::chrono::high_resolution_clock::now()};
    PlugboardDecryptInfo best_plugboard{};
    find_plugs(Op::INDEX_OF_COINCIDENCE, e_text, e_size, best_rings.front(), best_plugboard);
    std::cout << "FINAL SETTINGS:" << std::endl;
    best_plugboard.print(true);
//    auto pet{std::chrono::high_resolution_clock::now()};
//    auto dur{duration_cast<std::chrono::milliseconds>(pet - pst)};
//    std::cout << "plugs took " << dur.count() << " milliseconds" << std::endl;

    auto end_time {std::chrono::high_resolution_clock::now()};
    auto duration {duration_cast<std::chrono::milliseconds>(end_time - start_time)};
    if(duration.count() > 10000){
        std::cout << "decryption took " << duration.count() / 1000 << " seconds" << std::endl;
    }else {
        std::cout << "decryption took " << duration.count() << " milliseconds" << std::endl;
    }

    EnigmaConfig decrypt_config {
            best_plugboard.ring_info.rotor_info.rotors,
            best_plugboard.ring_info.rotor_info.rotor_pos,
            best_plugboard.ring_info.ring_pos,
            best_plugboard.ring_info.rotor_info.reflector,
            best_plugboard.plugboard
    };

//    em.set_config(decrypt_config);
    EnigmaMachine em {decrypt_config};
    em.encrypt_or_decrypt_file(input_filepath, output_filepath);

    delete e_text;
}

int BlindDecrypt::main(){
//    Op::format_input_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)");
//    return 0;

    int init_rotors[]{2, 5, 3};
    int init_rotor_pos[]{21, 19, 6};
    int init_rings[]{17, 19, 1};
    EnigmaConfig encrypt_config {
            init_rotors,
            init_rotor_pos,
            init_rings,
            'B',
//            "JM HO PQ LD UG ZF KS AN BX YW"
//            "QU IN VB LE CO KR WP ZH AS TY"
            "QU IN VB LE"
//            "IK BH RG NA PF"
//            "AF",
//            ""
    };

    EnigmaMachine em {encrypt_config};

    em.encrypt_or_decrypt_file(R"(.\in_out\plaintext.txt)", R"(.\in_out\encrypted.txt)");

    decrypt(R"(./in_out/encrypted.txt)", R"(./in_out/decrypted.txt)");

    std::cout << std::endl << "Done" << std::endl;
    return 0;
}