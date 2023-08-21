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
    stdo::Method method;
//    long double fitness;

    /* Semantic */
    RingDecryptInfo();

    RingDecryptInfo(const RotorDecryptInfo& rinfo, int* new_ring_pos, stdo::Method new_method, long double new_fitness);

    RingDecryptInfo(const RingDecryptInfo& other);

    ~RingDecryptInfo() override;

    RingDecryptInfo& operator=(const RingDecryptInfo& other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const override;
    void print() const override; // wraps print(false)

    [[nodiscard]] EnigmaConfig to_config() const override;
    void to_config(EnigmaConfig& config) const override;
};


#endif //ENIGMA_RINGDECRYPTINFO_H
