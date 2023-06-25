//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_PLUGBOARDDECRYPTINFO_H
#define ENIGMA_PLUGBOARDDECRYPTINFO_H


#include "RingDecryptInfo.h"
#include <iostream>
#include <iomanip>

// Stores results from plugboard decryption as well as the ring position decryption information used to attain this info
class PlugboardDecryptInfo{
public:
    RingDecryptInfo ring_info;
    std::string plugboard;
    Op::Method method;
    long double fitness;

    /*   Semantics    */
    // default constructor
    PlugboardDecryptInfo();

    // fielded constructor
    PlugboardDecryptInfo(const RingDecryptInfo& rinfo, std::string  new_plugboard, Op::Method new_method, long double new_fitness);

    // copy constructor
    PlugboardDecryptInfo(const PlugboardDecryptInfo& other);

    // destructor
    ~PlugboardDecryptInfo(); // default

    // assignment operator
    PlugboardDecryptInfo& operator=(const PlugboardDecryptInfo& other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const;
    void print() const; // wrapper for print(false)
};


#endif //ENIGMA_PLUGBOARDDECRYPTINFO_H
