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

/**
 * Defines weak ordering for lists of BlindDecrypt::PlugboardDecryptInfo structs. An item should come first in a list if
 * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
 * @param first The first item to compare.
 * @param second The second item to compare.
 * @return True if `first` is ordered before `second`, false otherwise.
 */
bool plug_decrypt_info_sort_order(const BlindDecrypt::PlugboardDecryptInfo& first, const BlindDecrypt::PlugboardDecryptInfo& second){
    return first.fitness >= second.fitness;
}

void BlindDecrypt::print_rotor_decrypt_info_list(const std::list<RotorDecryptInfo>& info) {
    using namespace std;
    cout << "ROTOR SETTINGS:" << endl;
    for(int i {}; i < 3; i++)
        cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "     ";
    cout << "REF" << "         " << "FIT" << endl;
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
    cout << "REF" << "         " << "FIT" << endl;
    for(auto & r: info) {
        cout << left << setw(3) << BlindDecrypt::itor(r.rotor_info.rotors[0]) << "  " << setw(2) << r.rotor_info.rotor_pos[0] << "  ring: " << setw(2) << r.ring_pos[0] << " |  "
             << left << setw(3) << BlindDecrypt::itor(r.rotor_info.rotors[1]) << "  " << setw(2) << r.rotor_info.rotor_pos[1] << "  ring: " << setw(2) << r.ring_pos[1] << " |  "
             << left << setw(3) << BlindDecrypt::itor(r.rotor_info.rotors[2]) << "  " << setw(2) << r.rotor_info.rotor_pos[2] << "  ring: " << setw(2) << r.ring_pos[2] << " |  "
                  << "REF: " << static_cast<char>(toupper(r.rotor_info.reflector)) << "  "
                  << " ->  " << r.fitness << endl;
    }
}

void BlindDecrypt::print_plugboard_decrypt_info_list(const std::list<PlugboardDecryptInfo> &info) {
    using namespace std;
    cout << "FINAL SETTINGS:" << endl;
    for(int i {}; i < 3; i++)
        cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "  " << "RING" << "        ";
    cout << "REF" << "         " << "FIT" << endl;
    for(auto & p: info) { 
        cout << left << setw(3) << BlindDecrypt::itor(p.ring_info.rotor_info.rotors[0]) << "  " << setw(2) << p.ring_info.rotor_info.rotor_pos[0] << "  ring: " << setw(2) << p.ring_info.ring_pos[0] << " |  "
             << left << setw(3) << BlindDecrypt::itor(p.ring_info.rotor_info.rotors[1]) << "  " << setw(2) << p.ring_info.rotor_info.rotor_pos[1] << "  ring: " << setw(2) << p.ring_info.ring_pos[1] << " |  "
             << left << setw(3) << BlindDecrypt::itor(p.ring_info.rotor_info.rotors[2]) << "  " << setw(2) << p.ring_info.rotor_info.rotor_pos[2] << "  ring: " << setw(2) << p.ring_info.ring_pos[2] << " |  "
             << "REF: " << static_cast<char>(toupper(p.ring_info.rotor_info.reflector)) << "  "
             << " ->  " << p.fitness << endl;
        cout << "WITH PLUGBOARD: " << p.plugboard << endl;
    }
}

double BlindDecrypt::calculate_fitness(BlindDecrypt::Method method, char *text, int text_size,
                                     const std::string& current_target) {
    switch(method){
        case INDEX_OF_COINCIDENCE:
            return static_cast<double>(IndexOfCoincidence::calculate(text, text_size));
            break;
        case CHARACTER_FREQUENCY:
            return CharacterFrequency::calculate(text, text_size);
            break;
        default:
            std::cout << "no decryption method selected for " << current_target << std::endl;
            return -1.0;
            break;
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
                              const std::list<RingDecryptInfo> &best_rings, std::list<PlugboardDecryptInfo>& best_plugboards) {
    (void) best_plugboards;

    EnigmaConfig config {};

    std::string fixed {};

    std::vector<char*> possible_pairs {};
    generate_plugboard_pair_permutations(possible_pairs);

    char* d_text = new char[text_size+1]{0};

    long double cur_fitness;
    long double best_fitness {};

    for(RingDecryptInfo rinfo: best_rings) {
        Ops::rep_arr3(config.rotors, rinfo.rotor_info.rotors);
        Ops::rep_arr3(config.rotor_pos, rinfo.rotor_info.rotor_pos);
        Ops::rep_arr3(config.ring_pos, rinfo.ring_pos);
        config.reflector = rinfo.rotor_info.reflector;
        config.plugboard = "";

        em.set_config(config);
        for (char *pair: possible_pairs) {
            char cur[] {pair[0], pair[1], '\0'};
            if(!fixed.empty()) fixed += " ";
            std::string cur_s {fixed + cur};
            em.set_plugboard_settings(cur_s);

            em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

            cur_fitness = calculate_fitness(method, d_text, text_size, "plugboard");

            if(best_plugboards.empty() || cur_fitness > best_plugboards.back().fitness){
                if(fixed.size() > 30){
                    fixed.erase(0, 3);
                }

                auto new_rotor_info = new RotorDecryptInfo {
                    .rotors = new int[3],
                    .rotor_pos = new int[3],
                    .reflector = rinfo.rotor_info.reflector,
                    .method = rinfo.rotor_info.method,
                    .fitness = rinfo.rotor_info.fitness
                };
                Ops::rep_arr3(new_rotor_info->rotors, rinfo.rotor_info.rotors);
                Ops::rep_arr3(new_rotor_info->rotor_pos, rinfo.rotor_info.rotor_pos);

                auto new_ring_info = new RingDecryptInfo {
                    .rotor_info = *new_rotor_info,
                    .ring_pos = new int[3],
                    .method = rinfo.method,
                    .fitness = rinfo.fitness
                };
                Ops::rep_arr3(new_ring_info->ring_pos, rinfo.ring_pos);

                auto new_good_plugboard = new PlugboardDecryptInfo {
                    .plugboard = *(new std::string {cur_s}),
                    .ring_info = *new_ring_info,
                    .method = method,
                    .fitness = cur_fitness
                };

                if(best_plugboards.size() >= 5){
                    best_plugboards.pop_back();
                }
                best_plugboards.push_back(*new_good_plugboard);
                best_plugboards.sort(plug_decrypt_info_sort_order);

                if(cur_fitness > best_fitness || best_plugboards.empty()) {
                    std::cout << "new best fitness: " << best_fitness << std::endl;
                    best_fitness = cur_fitness;
                    std::ofstream ofile{R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted_plugs.txt)"};
                    ofile << d_text;
                    ofile.close();
                }
            }

        }
    }
}

int main(){
    EnigmaConfig config {
            .rotors {3, 4, 5},
            .rotor_pos{17, 25, 3},
//            .ring_pos{9, 22, 17},
            .ring_pos{5, 10, 15},
            .reflector ='C',
//            .plugboard {"QU IN VB LE CO KR WP ZH AS TY"}
            .plugboard {"QU IN VB LE"}
//            .plugboard {""}
    };

    EnigmaMachine em {config};

    em.encrypt_or_decrypt_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)", R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)");

    int e_size {};
    char* e_text = Ops::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", &e_size);

    std::list<BlindDecrypt::RotorDecryptInfo> best_rotors {};

    auto start_time {std::chrono::high_resolution_clock ::now()};

//    BlindDecrypt::find_rotors(em, BlindDecrypt::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    BlindDecrypt::find_rotors(em, BlindDecrypt::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);
    std::cout << std::endl;
    BlindDecrypt::print_rotor_decrypt_info_list(best_rotors);
    std::cout << std::endl;

    std::list<BlindDecrypt::RingDecryptInfo> best_rings {};

//    BlindDecrypt::find_rings(em, BlindDecrypt::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors, best_rings);
    BlindDecrypt::find_rings(em, BlindDecrypt::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors, best_rings);
    BlindDecrypt::print_ring_decrypt_info_list(best_rings);


    std::list<BlindDecrypt::PlugboardDecryptInfo> best_configs {};
    BlindDecrypt::find_plugs(em, BlindDecrypt::CHARACTER_FREQUENCY, e_text, e_size, best_rings, best_configs);
    BlindDecrypt::print_plugboard_decrypt_info_list(best_configs);

    auto end_time {std::chrono::high_resolution_clock::now()};
    auto duration {duration_cast<std::chrono::seconds>(end_time - start_time)};
    std::cout << "decryption took " << duration.count() << " seconds" << std::endl;

    std::ofstream log_file {R"(J:\Programming\enigma\cmake-build-debug\in_out\log.txt)"};
    log_file << "decryption took " << duration.count() << " seconds" << std::endl;
    log_file.close();

    delete e_text;
    std::cout << std::endl << "Done" << std::endl;
    return 0;
}