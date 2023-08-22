/**
 * Misc debug functions used during testing. 
 *
 * Not important for normal use of program.
 **/
#include <iostream>
#include "Enigma/Headers/EnigmaMachine.h"
#include "Analysis/stdo.h"
#include <fstream>

// return true if no dups found, false otherwise (true is desired generally)
bool check_char_duping(std::string s1, std::string s2){
    uint32_t i {};
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
    uint32_t i {0};
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
    uint32_t i {0};
    while(i < length){
        if(sbuf1.at(i) != sbuf2.at(i)){
            return false;
        }
        i++;
    }
    return true;
}

void in_out_cycle(EnigmaMachine& em, const std::string& file1_n, const std::string& file2_n, const std::string& file3_n, int* rotor_pos){
    em.encrypt_or_decrypt(file1_n, file2_n);
    em.set_rotor_pos(rotor_pos);
    em.encrypt_or_decrypt(file2_n, file3_n);
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

