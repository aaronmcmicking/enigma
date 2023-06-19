//
// Created by aaron on 2023-06-17.
//

#include <iostream>
#include "KnownPlaintextSimple.h"

int KnownPlaintextSimple::calculate(const char *decrypted_text, long d_size, const char* plaintext, long p_size, int offset) {

    int fitness {};
    long final_read_position {offset + p_size};

    if(final_read_position > d_size){
        std::cout << "Invalid plaintext size and offset (" << final_read_position << " out of range for decrypted text with length " << d_size << ")" << std::endl;
        return -1;
    }

    std::cout << "known plaintext: ";
    for(int w {offset}; w < final_read_position; w++) std::cout << plaintext[w-offset];
    std::cout << std::endl;
    std::cout << "decrypted text: ";
    for(int j {offset}; j < final_read_position; j++) std::cout << decrypted_text[j];
    std::cout << std::endl;

    for(int i {offset}; i < final_read_position; i++){
        if(decrypted_text[i] == plaintext[i-offset]){
            fitness++;
        }else{
            fitness--;
        }
    }

    std::cout << "fitness = " << fitness << std::endl;

    return fitness;
}