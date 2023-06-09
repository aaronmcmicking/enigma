//
// Created by aaron on 2023-06-06.
//

#include <iostream>
#include "Decrypt.h"
#include "IndexOfCoincidence/IndexOfCoincidence.h"


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
        return "INVALID";
    }
    std::string str[] {"I", "II", "III", "IV", "V", "VI", "VII", "VIII"};
    return str[i-1];
}

void Decrypt::find_rotors(EnigmaMachine em, Decrypt::Method method, char* e_text, long text_size,
                          std::list<std::pair<std::pair<int *, int *>, long double>>& best_rotors) {
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
    std::queue<std::pair<std::pair<int *, int *>, long double>> cumulative_best_rotors; // contains pair<rotors, rotor pos>, fitness

    char* d_text = new char[text_size+1]{0};

    long double cur_fitness {};
    long double best_fitness {};

    for(std::vector<int> cur_rotors: rotor_perms){
        for(int r1_p {1}; r1_p <= 26; r1_p++){
            Ops::rep_arr3(config.rotors, cur_rotors[0], cur_rotors[1], cur_rotors[2]);
            for(int r2_p {1}; r2_p <= 26; r2_p++){
                for(int r3_p {1}; r3_p <= 26; r3_p++){
                    for(char ref {'a'}; ref <= 'c'; ref++){
                        if(r1_p == 1 && r2_p == 1 && r3_p == 1) {
                            if(ref == 'a')
                                std::cout << itor(cur_rotors[0]) << ", " << itor(cur_rotors[1]) << ", " << itor(cur_rotors[2]) << std::endl;
                        }

                        Ops::rep_arr3(config.rotor_pos, r1_p, r2_p, r3_p);
                        config.reflector = ref;

                        em.set_config(config);

                        em.encrypt_or_decrypt_arr_direct(d_text, e_text, text_size);

                        switch (method) {
                            case (Method::INDEX_OF_COINCIDENCE):
                                cur_fitness = IndexOfCoincidence::calculate(d_text, text_size);
//                                for(int i {0}; i < 10; i++) std::cout << d_text[i];
                                break;
                            default:
                                std::cout << "decrypt: no method selected" << std::endl;
                                return;
                        }

                        if(cur_fitness >= best_fitness){
                            best_fitness = cur_fitness;
                            if(best_fitness > 1.01) std::cout << "new best fitness: " << best_fitness << std::endl;
//                            EnigmaMachine::copy_config(best_config, config);
                            int* r = new int[3]{cur_rotors[0], cur_rotors[1], cur_rotors[2]};
                            int* rp = new int[3]{r1_p, r2_p, r3_p};
                            std::pair<int*, int*> rpair {r, rp};
                            std::pair<std::pair<int*, int*>, long double> npair {rpair, best_fitness};
                            cumulative_best_rotors.push(npair);
                            if(cumulative_best_rotors.size() > 10){
                                cumulative_best_rotors.pop();
                            }

                            std::ofstream ofile {R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted.txt)"};
                            ofile << d_text;
                            ofile.close();
                        } // cur_fitness >= best_fitness

                    } // ref
                } // r3_p
            } // r2_p
        } // r1_p
    } // rotor perms

    for(int i {0}; i < 10; i++){
        best_rotors.push_back(cumulative_best_rotors.front());
        cumulative_best_rotors.pop();
    }

    delete[] d_text;
}

void Decrypt::find_rings(EnigmaMachine em, Decrypt::Method method, const char *text,
                         std::vector<std::vector<int>> &best_ring_settings) {
    (void) em;
    (void) method;
    (void) text;
    (void) best_ring_settings;
}

void Decrypt::decrypt(Decrypt::Method method) {
    EnigmaConfig config {.rotors {1, 2, 3},
                         .rotor_pos{12, 25, 7},
                         .ring_pos{0, 0, 0},
                         .reflector ='B',
                         .plugboard {"QM AN SB DP OI CF RK UE HY"}
    };

    EnigmaMachine em {config};

    long double best_score {0};
    long double cur_score {0};
    EnigmaConfig best_config {{1, 1, 1}, {1, 1, 1}, {0, 0, 0}, 'a', ""};

    int d_size {};
    char* e_text = Ops::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", &d_size);
    char* d_text = new char[d_size];

    std::vector<std::vector<int>> rotor_perms {};
    generate_rotor_permutations(rotor_perms);

    for(std::vector<int> cur_rotor_pos: rotor_perms){
        for (int r1_p{1}; r1_p <= 26; r1_p++) {
            for (int r2_p{1}; r2_p <= 26; r2_p++) {
                for (int r3_p{1}; r3_p <= 26; r3_p++) {
                    for (char ref{'a'}; ref <= 'c'; ref++) {
                        if(r1_p == 1 && r2_p == 1 && r3_p == 1) {
                            if(ref == 'a')
                                std::cout << itor(cur_rotor_pos[0]) << ", " << itor(cur_rotor_pos[1]) << ", " << itor(cur_rotor_pos[2]) << std::endl;
                        }
//                                Ops::rep_arr3(config.rotors, r1, r2, r3);
                                Ops::rep_arr3(config.rotors, cur_rotor_pos[0], cur_rotor_pos[1], cur_rotor_pos[2]);
                                Ops::rep_arr3(config.rotor_pos, r1_p, r2_p, r3_p);
                                config.reflector = ref;

                                em.set_config(config);

//                                std::cout << "REF: " << ref << std::endl;

                                em.encrypt_or_decrypt_arr(d_text, e_text, d_size);

                                switch (method) {
                                    case (Method::INDEX_OF_COINCIDENCE):
                                        cur_score = IndexOfCoincidence::calculate(d_text, d_size);
                                        break;
                                    default:
                                        std::cout << "decrypt: no method selected" << std::endl;
                                        return;
                                }

                                if (cur_score > best_score) {
                                    best_score = cur_score;
                                    Ops::rep_arr3(best_config.rotors, cur_rotor_pos[0], cur_rotor_pos[1], cur_rotor_pos[2]);
                                    Ops::rep_arr3(best_config.rotor_pos, r1_p, r2_p, r3_p);
//                                    best_config.reflector = ref;

                                    std::ofstream ofile {R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted.txt)"};
                                    ofile << d_text;
                                    ofile.close();
                                    std::cout << "new best score: " << best_score << " (wrote to file)" << std::endl;

                                    std::ofstream ofile1 {R"(J:\Programming\enigma\cmake-build-debug\in_out\current_e_text.txt)"};
                                    ofile1 << e_text;
                                    ofile1.close();
//                                    best_config.plugboard = something
                                } // computing score
                            } // ref
                        } // r3 pos
                    } // r2 pos
                } // r1 pos
            }

    EnigmaMachine::print_config_object(best_config);
    std::ofstream ofile {R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted.txt)"};
    ofile << d_text;
    ofile.close();
    std::cout << "best score: " << best_score << std::endl;

    delete e_text;
    delete[] d_text;
}


int main(){
    EnigmaConfig config {
            .rotors {5, 3, 4},
            .rotor_pos{25, 7, 7},
            .ring_pos{9, 22, 17},
            .reflector ='C',
            .plugboard {"QP AL ZM XK SN DJ CH FB GU TY"}
    };

    EnigmaMachine em {config};

    em.encrypt_or_decrypt_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)", R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)");

    int e_size {};
    char* e_text = Ops::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", &e_size);

    std::list<std::pair<std::pair<int*, int*>, long double>> best_rotors {};

    auto start_time = std::chrono::high_resolution_clock::now();

    Decrypt::find_rotors(em, Decrypt::INDEX_OF_COINCIDENCE, e_text, e_size, best_rotors);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::for_each(best_rotors.begin(), best_rotors.end(), [&](const auto &item) {
        int* r {static_cast<std::pair<std::pair<int*, int*>, long double>>(item).first.first};
        int* rp {static_cast<std::pair<std::pair<int*, int*>, long double>>(item).first.second};
        long double fit {static_cast<std::pair<std::pair<int*, int*>, long double>>(item).second};
        std::cout << Decrypt::itor(r[0]) << ": " << rp[0] << "  " << Decrypt::itor(r[1]) << ": " << rp[1] << "  " << Decrypt::itor(r[2]) << ": " << rp[2] << " -> " << fit << std::endl;
    });

    std::cout << std::endl << "Finding rotors took " << duration.count() / 1000.0l << "s" << std::endl;

    //    Decrypt::decrypt(Decrypt::Method::INDEX_OF_COINCIDENCE);

//    std::cout << "IOC: " << IndexOfCoincidence::calculate_f(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)") << std::endl;
    delete e_text;
    std::cout << std::endl << "Done" << std::endl;
    return 0;
}