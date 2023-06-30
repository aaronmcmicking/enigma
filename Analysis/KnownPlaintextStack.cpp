//
// Created by aaron on 2023-06-19.
//

#include <iomanip>
#include <chrono>
#include <iostream>
#include "KnownPlaintextStack.h"

#include "Op.h"

void KnownPlaintextStack::generate_rotor_permutations(std::vector<std::vector<int>>& permutations) {
    permutations.clear();
    for(int i {1}; i <= 5; i++){
        for(int j {1}; j <= 5; j++){
            for(int w {1}; w <= 5; w++){
                if(i != j && i != w && j != w){ // get unique arrangements only
                    permutations.push_back(*new std::vector<int>{i, j, w});
                }
            }
        }
    }
}

void KnownPlaintextStack::generate_plugboard_pair_permutations(std::vector<char*> &permutations) {
    permutations.clear();
    for (char c1 {'A'}; c1 <= 'Z'; c1++) {
        for(char c2 {static_cast<char>(c1+1)}; c2 <= 'Z'; c2++){
            permutations.push_back(new char[]{c1, c2});
        }
    }
    char* n = new char[2]{' ', ' '}; // no plug is always an option
    permutations.push_back(n);
}

bool KnownPlaintextStack::strneq(const char *str1, const char *str2, int n) {
    for(int i {}; i < n; i++){
        if(str1[i] != str2[i]){
            return false;
        }
    }
    return true;
}

void KnownPlaintextStack::decrypt(const char *text, long size, const char* plaintext, long plaintext_size,
                                    EnigmaConfig& best_config) {

    std::stack<EnigmaConfig> config_stack;
    std::stack<EnigmaConfig> buffer_stack;


    std::cout << "text = " << text << std::endl;
    std::cout << "text size = " << size << std::endl;
    std::cout << "plaintext = " << plaintext << std::endl;
    std::cout << "plaintext size = " << plaintext_size << std::endl;


//    EnigmaConfig config{
//            .rotors {1, 2, 3},
//            .rotor_pos{1, 1, 1},
//            .ring_pos{0, 0, 0},
//            .reflector = 'a',
//            .plugboard {""}
//    };

    EnigmaConfig config {};

    EnigmaMachine em{config};

    char *d_text{new char[size + 1]};

    std::vector<std::vector<int>> rotor_perms{};
    generate_rotor_permutations(rotor_perms);

    std::vector<char *> plug_perms{};
    generate_plugboard_pair_permutations(plug_perms);


    // fill initial stack
//    for(int plain_char {}; plain_char < plaintext_size; plain_char++) {
//    generate_plugboard_pair_permutations(plug_perms);
//    generate_rotor_permutations(rotor_perms);

    for (std::vector<int> cur_rotors: rotor_perms) {
        for (int r3_p{1}; r3_p <= 26; r3_p++) {
            Op::arrcpy3(config.rotors, cur_rotors[0], cur_rotors[1], cur_rotors[2]);
            for (int r2_p{1}; r2_p <= 26; r2_p++) {
                for (int r1_p{1}; r1_p <= 26; r1_p++) {
                    for (char ref{'a'}; ref <= 'c'; ref++) {
                        if (r1_p == 1 && r2_p == 1 && r3_p == 1 && ref == 'a') {
                            using namespace Op;
                            std::cout << std::left << std::setw(4) << itor(cur_rotors[0]) << " "
                            << std::left << std::setw(4) << itor(cur_rotors[1]) << " "
                            << std::left << std::setw(4) << itor(cur_rotors[2]) << std::endl;
                        }

                        std::string fixed_plugs {};
                        for(char* plug_pair: plug_perms) {
//                        for(int ring1 {1}; ring1 <= 26; ring1 ++) {
//                            for (int ring2{1}; ring2 <= 26; ring2++) {
                            // print the current rotor configuration

                            std::string cur_plug {plug_pair[0], plug_pair[1]};

                            config.plugboard = fixed_plugs + " " + cur_plug;
                            Op::arrcpy3(config.rotor_pos, r1_p, r2_p, r3_p);
//                                    Op::arrcpy3(config.ring_pos, ring1, ring2, 1);
                            config.reflector = ref;

                            em.set_config(config);

//                            em.encrypt_or_decrypt_arr_direct(d_text, text, plain_char);
                            em.encrypt_or_decrypt_arr_direct(d_text, text, 1);

//                            if(strneq(d_text, plaintext, plain_char)){
                            if (d_text[0] == plaintext[0]) {
                                static EnigmaConfig n_config{};
                                EnigmaMachine::copy_config(n_config, config);
                                config_stack.push(n_config);
                            }
                        }
                    } // reflector
                } // r1 position
            } // r2 position
        } // r3 position
    } // rotors

//    } // ring2
//    } // ring1
//    } // plaintext chars

    static EnigmaConfig cur_config {};

    bool init {true};

    // reduce viable options
    {
        while (config_stack.size() > 1) {
            for (int plain_char{}; plain_char < plaintext_size; plain_char++) {
                    if (config_stack.empty()) {
                        std::cout << "empty stack, no viable rotor configuration" << std::endl;
                        return;
                    } else if (init || config_stack.size() % 10000 == 0) {
                        std::cout << "non-empty stack (" << config_stack.size() << "), continuing" << std::endl;
                        init = false;
                    }
                    cur_config = config_stack.top();
                    em.set_config(cur_config);
                    config_stack.pop();

                    em.encrypt_or_decrypt_arr_direct(d_text, text, plain_char);

                    if (strneq(d_text, plaintext, plain_char)) {
                        static EnigmaConfig pusher{};
                        EnigmaMachine::copy_config(pusher, cur_config);
                        buffer_stack.push(pusher);
                    }
                }
                while(!buffer_stack.empty()){
                    config_stack.push(buffer_stack.top());
                    buffer_stack.pop();
                }
//                init = true;
            } // plaintext

    }

    EnigmaMachine::copy_config(best_config, config_stack.top());
    std::cout << "ended with " << config_stack.size() << " elements in config_stack" << std::endl;
}

int strlength(const char* str){
    int count {};
    for(int i {}; str[i] != '\0'; i++){
        count++;
    }
    return count;
}

int KnownPlaintextStack::main() {

    int init_rotors[]{2, 5, 3};
    int init_rotor_pos[]{21, 19, 6};
    int init_rings[]{0, 0, 0};
    EnigmaConfig encrypt_config {
        init_rotors,
        init_rotor_pos,
        init_rings,
        'B',
//            "JM HO PQ LD UG ZF KS AN BX YW"
//            "QU IN VB LE CO KR WP ZH AS TY"
//            "QU IN VB LE"
//            "IK BH RG NA PF"
//            "AF",
        ""
    };

    EnigmaMachine em {encrypt_config};

    em.encrypt_or_decrypt_file(R"(.\in_out\plaintext.txt)", R"(.\in_out\encrypted.txt)");

    int e_size {};
    char* e_text = Op::load_from_file(R"(./in_out/encrypted.txt)", &e_size);

    char* plaintext {new char[]{"iproposet"}};
    int plaintext_size {strlength(plaintext)};

    EnigmaConfig best_config {};

    auto start_time {std::chrono::high_resolution_clock ::now()};

    decrypt(e_text, e_size, plaintext, plaintext_size, best_config);

    EnigmaMachine::print_config_object(best_config);

    auto end_time {std::chrono::high_resolution_clock::now()};
    auto duration {duration_cast<std::chrono::milliseconds>(end_time - start_time)};
    if(duration.count() > 10000){
        std::cout << "decryption took " << duration.count() / 1000 << " seconds" << std::endl;
    }else {
        std::cout << "decryption took " << duration.count() << " milliseconds" << std::endl;
    }

    std::cout << std::endl << "Done" << std::endl;

    return 0;
}