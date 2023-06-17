//
// Created by aaron on 2023-06-06.
//

#include <iostream>
#include "BlindDecrypt.h"
#include "IndexOfCoincidence/IndexOfCoincidence.h"
#include "CharacterFrequency/CharacterFrequency.h"
#include <cmath>
#include <iomanip>
#include <chrono>

/**
 * Defines weak ordering for lists of BlindDecrypt::RotorDecryptInfo structs. An item should come first in a list if
 * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
 * @param first The first item to compare.
 * @param second The second item to compare.
 * @return True if `first` is ordered before `second`, false otherwise.
 */
bool rotor_decrypt_info_sort_order(const BlindDecrypt::RotorDecryptInfo& first, const BlindDecrypt::RotorDecryptInfo& second){
    return first.fitness >= second.fitness;
}

/**
 * Defines weak ordering for lists of BlindDecrypt::RingDecryptInfo structs. An item should come first in a list if
 * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
 * @param first The first item to compare.
 * @param second The second item to compare.
 * @return True if `first` is ordered before `second`, false otherwise.
 */
bool ring_decrypt_info_sort_order(const BlindDecrypt::RingDecryptInfo& first, const BlindDecrypt::RingDecryptInfo& second){
    return first.fitness >= second.fitness;
}

void BlindDecrypt::print_rotor_decrypt_info_list(const std::list<RotorDecryptInfo>& info) {
    using namespace std;
    cout << "ROTOR SETTINGS:" << endl;
    for(int i {}; i < 3; i++)
        cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "     ";
    cout << "REF" << "          " << "FITNESS" << endl;
//    cout << endl;
    for(auto& r: info){
        cout << left << setw(3) << BlindDecrypt::itor(r.rotors[0]) << "  " << left << setw(2) << r.rotor_pos[0] << "  |  "
                  << left << setw(3) << BlindDecrypt::itor(r.rotors[1]) << "  " << left << setw(2) << r.rotor_pos[1] << "  |  "
                  << left << setw(3) << BlindDecrypt::itor(r.rotors[2]) << "  " << left << setw(2) << r.rotor_pos[2] << "  |  "
                  << "REF: " << static_cast<char>(toupper(r.reflector)) << "  "
                  << " ->  " << r.fitness << endl;
    }
}

void BlindDecrypt::print_ring_decrypt_info_list(const std::list<RingDecryptInfo> &info) {
    using namespace std;
    cout << "RING SETTINGS:" << endl;
    for(int i {}; i < 3; i++)
        cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "  " << "RING" << "        ";
    cout << "REF" << "          " << "FITNESS" << endl;
    for(auto & r: info) {
        cout << left << setw(3) << BlindDecrypt::itor(r.rotor_info.rotors[0]) << "  " << setw(2) << r.rotor_info.rotor_pos[0] << "  ring: " << setw(2) << r.ring_pos[0] << " |  "
             << left << setw(3) << BlindDecrypt::itor(r.rotor_info.rotors[1]) << "  " << setw(2) << r.rotor_info.rotor_pos[1] << "  ring: " << setw(2) << r.ring_pos[1] << " |  "
             << left << setw(3) << BlindDecrypt::itor(r.rotor_info.rotors[2]) << "  " << setw(2) << r.rotor_info.rotor_pos[2] << "  ring: " << setw(2) << r.ring_pos[2] << " |  "
                  << "REF: " << static_cast<char>(toupper(r.rotor_info.reflector)) << "  "
                  << " ->  " << r.fitness << endl;
    }
}

void BlindDecrypt::print_plugboard_decrypt_info(const PlugboardDecryptInfo& info) {
    using namespace std;
    cout << "FINAL SETTINGS:" << endl;
    for(int i {}; i < 3; i++)
        cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "  " << "RING" << "        ";
    cout << "REF" << "          " << "FITNESS" << endl;
        cout << left << setw(3) << BlindDecrypt::itor(info.ring_info.rotor_info.rotors[0]) << "  " << setw(2) << info.ring_info.rotor_info.rotor_pos[0] << "  ring: " << setw(2) << info.ring_info.ring_pos[0] << " |  "
             << left << setw(3) << BlindDecrypt::itor(info.ring_info.rotor_info.rotors[1]) << "  " << setw(2) << info.ring_info.rotor_info.rotor_pos[1] << "  ring: " << setw(2) << info.ring_info.ring_pos[1] << " |  "
             << left << setw(3) << BlindDecrypt::itor(info.ring_info.rotor_info.rotors[2]) << "  " << setw(2) << info.ring_info.rotor_info.rotor_pos[2] << "  ring: " << setw(2) << info.ring_info.ring_pos[2] << " |  "
             << "REF: " << static_cast<char>(toupper(info.ring_info.rotor_info.reflector)) << "  "
             << " ->  " << info.fitness << endl;
        cout << "WITH PLUGBOARD: " << info.plugboard << endl;
}

double BlindDecrypt::calculate_fitness(BlindDecrypt::Method method, char *text, int text_size,
                                     const std::string& current_target) {
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

std::string BlindDecrypt::itor(int i){
    if(!EMOps::is_in_range(i, 1, 8)){
        return "INVALID NUMERAL";
    }
    std::string str[] {"I", "II", "III", "IV", "V", "VI", "VII", "VIII"};
    return str[i-1];
}

void BlindDecrypt::find_rotors(EnigmaMachine em, BlindDecrypt::Method method, const char* e_text, long text_size,
                               std::list<RotorDecryptInfo>& best_rotors) {
    std::vector<std::vector<int>> rotor_positions {};
    generate_rotor_permutations(rotor_positions);

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

    long double cur_fitness;
    long double best_fitness {};

    for(std::vector<int> cur_rotors: rotor_positions){
        for(int r1_p {1}; r1_p <= 26; r1_p++){
            Ops::rep_arr3(config.rotors, cur_rotors[0], cur_rotors[1], cur_rotors[2]);
            for(int r2_p {1}; r2_p <= 26; r2_p++){
                for(int r3_p {1}; r3_p <= 26; r3_p++){
                    for(char ref {'a'}; ref <= 'c'; ref++){
                        // print the current rotor configuration
                        if(r1_p == 1 && r2_p == 1 && r3_p == 1 && ref == 'a') {
                                std::cout   << std::left << std::setw(4) << itor(cur_rotors[0]) << " "
                                            << std::left << std::setw(4) << itor(cur_rotors[1]) << " "
                                            << std::left << std::setw(4) << itor(cur_rotors[2]) << std::endl;
                        }

                        // set new rotor settings
                        Ops::rep_arr3(config.rotor_pos, r1_p, r2_p, r3_p);
                        config.reflector = ref;
                        em.set_config(config);

                        // decrypt
                        em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                        // analyze
                        cur_fitness = calculate_fitness(method, d_text, text_size, "rotor settings");

                        // if a good rotor configuration was found, store it
                        if(best_rotors.empty() || cur_fitness >= best_rotors.back().fitness){
                            int* r = new int[3]{cur_rotors[0], cur_rotors[1], cur_rotors[2]};
                            int* rp = new int[3]{r1_p, r2_p, r3_p};

                            RotorDecryptInfo* ninfo{new RotorDecryptInfo {
                                                            .rotors = r,
                                                            .rotor_pos = rp,
                                                            .reflector = ref,
                                                            .method = method,
                                                            .fitness = cur_fitness
                                                    }};

                            if(best_rotors.size() >= 10) best_rotors.pop_back();
                            best_rotors.push_back(*ninfo);
                            best_rotors.sort(rotor_decrypt_info_sort_order);

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

void BlindDecrypt::find_rings(EnigmaMachine em, BlindDecrypt::Method method, const char *e_text, long text_size,
                              const std::list<RotorDecryptInfo>& best_rotors, std::list<RingDecryptInfo>& best_rings){

    EnigmaConfig config {
            .rotors {1, 2, 3},
            .rotor_pos{1, 1, 1},
            .ring_pos{0, 0, 0},
            .reflector = 'a',
            .plugboard {""}
    };

    char* d_text {new char[text_size+1]{0}};

    long double cur_fitness {};
    long double best_fitness {};

    auto rotor_it {best_rotors.cbegin()};
    for(int i {0}; i < 5; i++){
        auto rinfo {rotor_it};
        rotor_it++;
        Ops::rep_arr3(config.rotors, rinfo->rotors);
        Ops::rep_arr3(config.rotor_pos, rinfo->rotor_pos);
        config.reflector = rinfo->reflector;
        for (int r1{1}; r1 <= 26; r1++) {
            for (int r2{1}; r2 <= 26; r2++) {
//                for (int r3{1}; r3 <= 26; r3++) {
//                    Ops::rep_arr3(config.ring_pos, r1, r2, r3);
                    Ops::rep_arr3(config.ring_pos, r1, r2, 1);

                    em.set_config(config);

                    em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                cur_fitness = calculate_fitness(method, d_text, text_size, "ring settings");

                    if(best_rings.empty() || cur_fitness >= best_rings.back().fitness){
                        static RotorDecryptInfo rninfo {
                            .rotors = new int[3],
                            .rotor_pos = new int[3],
                            .reflector {},
                            .method {},
                            .fitness {}
                        };

                        // yuck
                        Ops::rep_arr3(rninfo.rotors, rinfo->rotors);
                        Ops::rep_arr3(rninfo.rotor_pos, rinfo->rotor_pos);
                        rninfo.reflector = rinfo->reflector;
                        rninfo.fitness = rinfo->fitness;
                        rninfo.method = rinfo->method;

                        RingDecryptInfo * ninfo{new RingDecryptInfo {
                            .rotor_info {rninfo},
//                            .ring_pos = new int[3]{r1, r2, r3},
                            .ring_pos = new int[3]{r1, r2, 1},
                            .method = method,
                            .fitness = cur_fitness
                        }};

                        if(best_rings.size() >= 5) best_rings.pop_back();
                        best_rings.push_back(*ninfo);
                        best_rings.sort(ring_decrypt_info_sort_order);

                        // if this is the best rotor configuration so far, write it's associated decryption to disk
                        if(cur_fitness > best_fitness || best_rings.empty()) {
//                            std::cout << "new best fitness: " << best_fitness << std::endl;
                            best_fitness = cur_fitness;
                            std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted_rings.txt)"};
                            ofile << d_text;
                            ofile.close();
                        }
                    } // should add to best settings

//                } // r3
            } // r2
        } // r1
    } // best rotor positions

    delete[] d_text;
}

void BlindDecrypt::find_plugs(EnigmaMachine em, BlindDecrypt::Method method, const char *e_text, long text_size,
                              const RingDecryptInfo& best_ring, PlugboardDecryptInfo& best_plugboard) {
    EnigmaConfig config {};
    Ops::rep_arr3(config.rotors, best_ring.rotor_info.rotors);
    Ops::rep_arr3(config.rotor_pos, best_ring.rotor_info.rotor_pos);
    Ops::rep_arr3(config.ring_pos, best_ring.ring_pos);
    config.reflector = best_ring.rotor_info.reflector;
    config.plugboard = "";
    em.set_config(config);

    std::vector<char*> possible_pairs {};
    generate_plugboard_pair_permutations(possible_pairs);

    char* d_text = new char[text_size+1]{0};

    double best_fitness_on_cycle {};
    char* best_pair_on_cycle {new char[3]{}};
    double cur_fitness;
    std::string fixed {};

    for(int i {}; i < 10; i++) {
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
                Ops::rep_arr(best_pair_on_cycle, cur, 3);
            }

            if(possible_pairs.back()[0] == pair[0] && possible_pairs.back()[1] == pair[1]){
                fixed += " ";
                fixed += best_pair_on_cycle;
                best_fitness_on_cycle = 0;
            }
        }
    }

    config.plugboard = fixed;
    em.set_config(config);
    em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);
    double final_fitness = calculate_fitness(method, d_text, text_size, "plugboard");

    std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted_plugs.txt)"};
    ofile << d_text;
    ofile.close();

    best_plugboard = *(new PlugboardDecryptInfo {});
    best_plugboard.ring_info = *(new RingDecryptInfo {
        .rotor_info {
            *new RotorDecryptInfo {
               .rotors = new int[3],
               .rotor_pos = new int[3],
               .reflector = best_ring.rotor_info.reflector,
               .method = best_ring.rotor_info.method,
               .fitness = best_ring.rotor_info.fitness
            } },
        .ring_pos = new int[3],
        .method = best_ring.method,
        .fitness = best_ring.fitness
    });
    // copy rotorbox info
    Ops::rep_arr3(best_plugboard.ring_info.rotor_info.rotors, best_ring.rotor_info.rotors);
    Ops::rep_arr3(best_plugboard.ring_info.rotor_info.rotor_pos, best_ring.rotor_info.rotor_pos);

    // copy ring info
    Ops::rep_arr3(best_plugboard.ring_info.ring_pos, best_ring.ring_pos);

    // new plugboard info
    best_plugboard.plugboard = fixed;
    best_plugboard.method = method;
    best_plugboard.fitness = final_fitness;

//    std::cout << "fixed = " << fixed << std::endl;
//    std::cout << "config.plugboard = " << config.plugboard << std::endl;
//    std::cout << "e_text = " << e_text << std::endl;
//    std::cout << std::endl << "actual plugboard: " << std::endl;
//    em.get_plugboard().print(false);
//    std::cout << std::endl;
//    EnigmaMachine::print_config_object(config);

    delete[] d_text;
}

int BlindDecrypt::main(){
//    Ops::format_input_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)");
//    return 0;

    EnigmaConfig encrypt_config {
            .rotors {2, 5, 3},
            .rotor_pos{21, 19, 6},
//            .ring_pos{9, 22, 17},
            .ring_pos{7, 19, 3},
//            .ring_pos{26, 26, 26},
//            .ring_pos{0, 0, 0},
            .reflector = 'B',
//            .plugboard {"JM HO PQ LD UG ZF KS AN BX YW"}
//            .plugboard {"QU IN VB LE CO KR WP ZH AS TY"}
            .plugboard {"QU IN VB LE"}
//            .plugboard {"IK BH RG NA PF"}
//            .plugboard {""}
    };

    EnigmaMachine em {encrypt_config};

    em.encrypt_or_decrypt_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)", R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)");

    int e_size {};
    char* e_text = Ops::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", &e_size);

    std::list<RotorDecryptInfo> best_rotors {};

    auto start_time {std::chrono::high_resolution_clock ::now()};

//    find_rotors(em, INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    find_rotors(em, INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    std::cout << std::endl;
    print_rotor_decrypt_info_list(best_rotors);
    std::cout << std::endl;

    std::list<RingDecryptInfo> best_rings {};

//    find_rings(em, INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors, best_rings);
    find_rings(em, INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors, best_rings);
    print_ring_decrypt_info_list(best_rings);
    std::cout << std::endl;


    PlugboardDecryptInfo best_plugboard {};
    find_plugs(em, INDEX_OF_COINCIDENCE, e_text, e_size, best_rings.front(), best_plugboard);
    print_plugboard_decrypt_info(best_plugboard);

    auto end_time {std::chrono::high_resolution_clock::now()};
    auto duration {duration_cast<std::chrono::seconds>(end_time - start_time)};
    std::cout << "decryption took " << duration.count() << " seconds" << std::endl;

    std::ofstream log_file {R"(J:\Programming\enigma\cmake-build-debug\in_out\log.txt)"};
    log_file << "decryption took " << duration.count() << " seconds" << std::endl;
    log_file.close();

    EnigmaConfig decrypt_config {
        .rotors = {},
        .rotor_pos = {},
        .ring_pos = {},
        .reflector = best_plugboard.ring_info.rotor_info.reflector,
        .plugboard = best_plugboard.plugboard
    };

    Ops::rep_arr3(decrypt_config.rotors, best_plugboard.ring_info.rotor_info.rotors);
    Ops::rep_arr3(decrypt_config.rotor_pos, best_plugboard.ring_info.rotor_info.rotor_pos);
    Ops::rep_arr3(decrypt_config.ring_pos, best_plugboard.ring_info.ring_pos);

    em.set_config(decrypt_config);
    em.encrypt_or_decrypt_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted.txt)");

    delete e_text;
    std::cout << std::endl << "Done" << std::endl;
    return 0;
}