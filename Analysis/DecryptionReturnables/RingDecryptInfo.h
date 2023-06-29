//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_RINGDECRYPTINFO_H
#define ENIGMA_RINGDECRYPTINFO_H

#include "RotorDecryptInfo.h"

// Stores results from ring position decrypt as well as the rotor decryption information used to attain this info
class RingDecryptInfo: public DecryptInfo{
public:
    RotorDecryptInfo rotor_info {};
    int* ring_pos;
    Op::Method method;
//    long double fitness;

    /* Semantic */
    // default constructor
    RingDecryptInfo();

    // fielded constructor
    RingDecryptInfo(const RotorDecryptInfo& rinfo, int* new_ring_pos, Op::Method new_method, long double new_fitness);

    // copy constructor
    RingDecryptInfo(const RingDecryptInfo& other);

    // destructor
    ~RingDecryptInfo() override;

    // assignment operator
    RingDecryptInfo& operator=(const RingDecryptInfo& other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const override;
    void print() const override; // wraps print(false)

    EnigmaConfig to_config() override;
    void to_config(EnigmaConfig& config) override;
};


#endif //ENIGMA_RINGDECRYPTINFO_H
