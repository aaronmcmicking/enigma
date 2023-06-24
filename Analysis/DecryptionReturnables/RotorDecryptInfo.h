//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_ROTORDECRYPTINFO_H
#define ENIGMA_ROTORDECRYPTINFO_H

#include "../Op.h"

// Stores result from rotor decryption
class RotorDecryptInfo{
public:

    int* rotors;
    int* rotor_pos;
    char reflector;
    Op::Method method;
    long double fitness;

    // default constructor
    RotorDecryptInfo();

    // fielded constructor
    RotorDecryptInfo(int* new_rotors, int* new_rotor_pos, char ref, Op::Method new_method, long double new_fitness);

    // copy constructor
    RotorDecryptInfo(const RotorDecryptInfo& other);

    // destructor
    ~RotorDecryptInfo();

    // copy assignment operator
    RotorDecryptInfo& operator=(const RotorDecryptInfo& other);
};


#endif //ENIGMA_ROTORDECRYPTINFO_H
