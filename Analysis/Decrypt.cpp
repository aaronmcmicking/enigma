//
// Created by aaron on 2023-06-06.
//

#include <iostream>
#include "Decrypt.h"
#include "IndexOfCoincidence/IndexOfCoincidence.h"
#include "../Enigma/Headers/EnigmaMachine.h"

std::string itor(int i){
    std::string str {};
    switch(i){
        case 1:
            str = "I";
            break;
        case 2:
            str = "II";
            break;
        case 3:
            str = "III";
            break;
        case 4:
            str = "IV";
            break;
        case 5:
            str = "V";
            break;
        case 6:
            str = "VI";
            break;
        case 7:
            str = "VII";
            break;
        case 8:
            str = "VIII";
            break;
        default:
            str = "UNVALID";
            break;
    }
    return str;
}

void Decrypt::decrypt(Decrypt::Method method) {
    EnigmaConfig config {.rotors {1, 2, 3},
                         .rotor_pos{1, 1, 1},
                         .reflector ='B',
                         .plugboard {""}
    };

    EnigmaMachine em {config};

    long double best_score {0};
    long double cur_score {0};
    EnigmaConfig best_config {{1, 1, 1}, {1, 1, 1}, 'a', ""};

    int d_size {};
    char* e_text = Ops::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)", &d_size);
    char* d_text = new char[d_size];

    for(int r1 {1}; r1 <= 5; r1++) {
        for (int r2{1}; r2 <= 5; r2++) {
            for (int r3{1}; r3 <= 5; r3++) {
                for (int r1_p{1}; r1_p <= 26; r1_p++) {
                    for (int r2_p{1}; r2_p <= 26; r2_p++) {
                        for (int r3_p{1}; r3_p <= 26; r3_p++) {
//                            for (char ref{'a'}; ref <= 'c'; ref++) {
                                if(r1_p == 1 && r2_p == 1 && r3_p == 1) {
                                    std::cout << itor(r1) << ", " << itor(r2) << ", " << itor(r3) << std::endl;
                                }
                                Ops::rep_arr3(config.rotors, r1, r2, r3);
                                Ops::rep_arr3(config.rotor_pos, r1_p, r2_p, r3_p);
//                                config.reflector = ref;

                                em.set_config(config);

//                                std::cout << "REF: " << ref << std::endl;

                                em.encrypt_or_decrypt_arr(d_text, e_text, d_size);

                                switch (method) {
                                    case (Method::INDEX_OF_COINCIDENCE):
                                        cur_score = IndexOfCoincidence::calculate(d_text);
                                        break;
                                    default:
                                        std::cout << "decrypt: no method selected" << std::endl;
                                        return;
                                }

                                if (cur_score > best_score) {
                                    best_score = cur_score;
                                    Ops::rep_arr3(best_config.rotors, r1, r2, r3);
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
//                            } // ref
                        } // r3 pos
                    } // r2 pos
                } // r1 pos
            } // r3
        } // r2
    } // r1

    EnigmaMachine::print_config_object(best_config);
    std::ofstream ofile {R"(J:\Programming\enigma\cmake-build-debug\in_out\decrypted.txt)"};
    ofile << d_text;
    ofile.close();
    std::cout << "best score: " << best_score << std::endl;

    delete e_text;
    delete[] d_text;
}


int main(){
    EnigmaConfig config {.rotors {1, 2, 3},
            .rotor_pos{1, 1, 1},
            .reflector ='A',
            .plugboard {""}
    };

    EnigmaMachine em {config};

    em.encrypt_or_decrypt_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)", R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)");

    Decrypt::decrypt(Decrypt::Method::INDEX_OF_COINCIDENCE);

//    std::cout << "IOC: " << IndexOfCoincidence::calculate_f(R"(J:\Programming\enigma\cmake-build-debug\in_out\encrypted.txt)") << std::endl;
    std::cout << "Done" << std::endl;
    return 0;
}