//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_ROTORDECRYPTINFO_H
#define ENIGMA_ROTORDECRYPTINFO_H

#include "../Op.h"
#include "DecryptInfo.h"

// Stores result from rotor decryption
class RotorDecryptInfo: public DecryptInfo{
public:
    int* rotors;
    int* rotor_pos;
    char reflector;
    Op::Method method;
//    long double fitness;

    /* Semantic */
    // default constructor
    RotorDecryptInfo();

    // fielded constructor
    RotorDecryptInfo(int* new_rotors, int* new_rotor_pos, char ref, Op::Method new_method, long double new_fitness);

    // copy constructor
    RotorDecryptInfo(const RotorDecryptInfo &other);

    // destructor
    ~RotorDecryptInfo() override;

    // copy assignment operator
    RotorDecryptInfo &operator=(const RotorDecryptInfo &other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const override;
    void print() const override; // wraps print(false)

    [[nodiscard]] EnigmaConfig to_config() const override;
    void to_config(EnigmaConfig& config) const override;
};


#endif //ENIGMA_ROTORDECRYPTINFO_H
