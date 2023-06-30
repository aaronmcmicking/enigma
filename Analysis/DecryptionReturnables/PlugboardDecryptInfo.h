//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_PLUGBOARDDECRYPTINFO_H
#define ENIGMA_PLUGBOARDDECRYPTINFO_H


#include "RingDecryptInfo.h"
#include <iostream>
#include <iomanip>

// Stores results from plugboard decryption as well as the ring position decryption information used to attain this info
class PlugboardDecryptInfo: public DecryptInfo{
public:
    RingDecryptInfo ring_info;
    std::string plugboard;
    stdo::Method method;
//    long double fitness;

    /*   Semantics    */
    // default constructor
    PlugboardDecryptInfo();

    // fielded constructor
    PlugboardDecryptInfo(const RingDecryptInfo& rinfo, std::string  new_plugboard, stdo::Method new_method, long double new_fitness);

    // copy constructor
    PlugboardDecryptInfo(const PlugboardDecryptInfo& other);

    // destructor
    ~PlugboardDecryptInfo() override; // default

    // assignment operator
    PlugboardDecryptInfo& operator=(const PlugboardDecryptInfo& other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const override;
    void print() const override; // wraps print(false)

    [[nodiscard]] EnigmaConfig to_config() const override;
    void to_config(EnigmaConfig& config) const override;
};


#endif //ENIGMA_PLUGBOARDDECRYPTINFO_H
