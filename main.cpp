#include <iostream>
#include "Enigma/Headers/EnigmaMachine.h"
#include "Analysis/Op.h"
#include "Analysis/BlindDecrypt.h"
#include "Analysis/KnownPlaintextStack.h"
#include "Testing.cpp"
#include <fstream>

// return true if no dups found, false otherwise (true is desired generally)
bool check_char_duping(std::string s1, std::string s2){
    uint i {};
    unsigned long long const s1_l {s1.length()};
    unsigned long long const s2_l {s2.length()};

    while(i < s1_l && i < s2_l){
        if(s1.at(i) == s2.at(i)){
            return false;
        }
        i++;
    }
    return true;
}

bool fcheck_char_duping(const std::string& file1_n, const std::string& file2_n){
    char buf1[MAX_INPUT_STRING_LENGTH] {};
    char buf2[MAX_INPUT_STRING_LENGTH] {};

    std::ifstream file1 {file1_n};
    file1.read(buf1, MAX_INPUT_STRING_LENGTH);

    std::ifstream file2 {file2_n};
    file2.read(buf2, MAX_INPUT_STRING_LENGTH);

    std::string sbuf1 {buf1};
    std::string sbuf2 {buf2};

    unsigned long long length = sbuf1.length() < sbuf2.length() ? sbuf1.length() : sbuf2.length(); // get min length
    uint i {0};
    while(i < length){
        if(sbuf1.at(i) == sbuf2.at(i)){
            return false;
        }
        i++;
    }
    return true;
}

bool fcheck_identical(const std::string& file1_n, const std::string& file2_n){
    char buf1[MAX_INPUT_STRING_LENGTH] {};
    char buf2[MAX_INPUT_STRING_LENGTH] {};

    std::ifstream file1 {file1_n};
    file1.read(buf1, MAX_INPUT_STRING_LENGTH);

    std::ifstream file2 {file2_n};
    file2.read(buf2, MAX_INPUT_STRING_LENGTH);

    std::string sbuf1 {buf1};
    std::string sbuf2 {buf2};

    unsigned long long length = sbuf1.length() < sbuf2.length() ? sbuf1.length() : sbuf2.length(); // get min length
    uint i {0};
    while(i < length){
        if(sbuf1.at(i) != sbuf2.at(i)){
            return false;
        }
        i++;
    }
    return true;
}

void in_out_cycle(EnigmaMachine& em, const std::string& file1_n, const std::string& file2_n, const std::string& file3_n, int* rotor_pos){
    em.encrypt_or_decrypt_file(file1_n, file2_n);
    em.set_rotor_pos(rotor_pos);
    em.encrypt_or_decrypt_file(file2_n, file3_n);
}


bool verification_cycle(EnigmaMachine& em, const std::string& file1_n, const std::string& file2_n, const std::string& file3_n, EnigmaConfig config) {
    bool status;
    std::remove(file2_n.c_str()); std::remove(file3_n.c_str()); // remove the output files

    em.set_config(config);

    in_out_cycle(em, file1_n, file2_n, file3_n, config.rotor_pos);
    status = fcheck_char_duping(file1_n, file2_n);
    if(!status) return false;
    status = fcheck_identical(file1_n, file3_n);
    return status;
}

void print_status(bool status){
    if(!status) {
        std::cout << "Verification failed" << std::endl;
        exit(1);
    }else{
        std::cout << "Verification was successful" << std::endl;
    }
}

void print_config(const EnigmaConfig& config){
    std::cout << "rotors = ";
    for(int i{}; i < 3; i++) {
        std::cout << config.rotors[i] << " ";
    }
    std::cout << std::endl << "pos = ";
    for(int i{}; i < 3; i++) {
        std::cout << config.rotor_pos[i] << " ";
    }
    std::cout << std::endl << "ring pos = ";
    for(int i{}; i < 3; i++) {
        std::cout << config.ring_pos[i] << " ";
    }
    std::cout << std::endl << "ref = " << config.reflector << std::endl;
    std::cout << "plugboard = " << config.plugboard << std::endl;
}

std::string get_path(){
    std::ifstream path_file {"pathname.txt"};
    char path_buf[100] {};
    path_file.read(path_buf, 100);
    return std::string {path_buf};
}

#define USING_MAINCPP
#ifdef USING_MAINCPP
int main(){

    int irot[3]{1, 2, 3};
    int irotp[]{4, 5, 6};
    RotorDecryptInfo rotor_info {
        irot,
        irotp,
        'A',
        Op::INDEX_OF_COINCIDENCE,
        7.77
    };

    rotor_info.print(true);

    /*
    RotorDecryptInfo rotor_info {new int[]{1, 2, 3}, new int[]{4, 5, 6}, 'C', Op::INDEX_OF_COINCIDENCE, 10.0};

    EnigmaConfig config;
    rotor_info.to_config(config);
    EnigmaMachine::print_config_object(config);
    EnigmaMachine::print_config_object(rotor_info.to_config());
    std::cout << std::endl << std::endl;

    RingDecryptInfo ring_info {rotor_info, new int[3]{7, 8, 9}, Op::CHARACTER_FREQUENCY, 5.5};

    ring_info.to_config(config);
    EnigmaMachine::print_config_object(config);
    EnigmaMachine::print_config_object(ring_info.to_config());
    std::cout << std::endl << std::endl;

    PlugboardDecryptInfo plug_info {ring_info, "AH FD NJ", Op::KNOWN_PLAINTEXT_SIMPLE, 7.77};

    plug_info.to_config(config);
    EnigmaMachine::print_config_object(config);
    EnigmaMachine::print_config_object(plug_info.to_config());
    std::cout << std::endl << std::endl;
    */


    BlindDecrypt::main();
//
//    KnownPlaintextStack::main();

//    bool status {};
//
//    std::string path {get_path()};
//
//    std::string file1_n {path + "plaintext.txt"};
//    std::string file2_n {path + "encrypted.txt"};
//    std::string file3_n {path + "decrypted.txt"};
//
//    Op::format_input_file(file1_n);
//
//    EnigmaConfig config {.rotors {2, 1, 3}, .rotor_pos {3, 5, 7}, .reflector = 'A', .plugboard {"TG NJ AZ DF CV PO WM"}};
//
//    EnigmaMachine em {config};
//
//    status = verification_cycle(em, file1_n, file2_n, file3_n, config);
//    print_status(status);
//
//    Op::arrcpy3(config.rotor_pos, 12, 26, 8);
//    Op::arrcpy3(config.rotors, 3, 5, 1);
//    config.reflector = 'c';
//    config.plugboard = "LA MD JC NE ZU QO";
//    status = verification_cycle(em, file1_n, file2_n, file3_n, config);
//    print_status(status);
//
//    Op::arrcpy3(config.rotor_pos, 26, 26, 26);
//    Op::arrcpy3(config.rotors, 5, 5, 5);
//    config.reflector = 'a';
//    config.plugboard = "";
//    status = verification_cycle(em, file1_n, file2_n, file3_n, config);
//    print_status(status);
//
//    Op::arrcpy3(config.rotor_pos, 1, 26, 26);
//    Op::arrcpy3(config.rotors, 5, 4, 3);
//    config.reflector = 'b';
//    config.plugboard = "";
//    status = verification_cycle(em, file1_n, file2_n, file3_n, config);
//    print_status(status);
//
//    print_config(config);



    return 0;
}
#endif