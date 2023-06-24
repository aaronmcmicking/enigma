//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_PLUGBOARDDECRYPTINFO_H
#define ENIGMA_PLUGBOARDDECRYPTINFO_H


#include "RingDecryptInfo.h"

// Stores results from plugboard decryption as well as the ring position decryption information used to attain this info
class PlugboardDecryptInfo{
public:
    RingDecryptInfo ring_info;
    std::string plugboard;
    Op::Method method;
    long double fitness;

    PlugboardDecryptInfo();

    PlugboardDecryptInfo(const RingDecryptInfo& rinfo, std::string  new_plugboard, Op::Method new_method, long double new_fitness);

    PlugboardDecryptInfo(const PlugboardDecryptInfo& other);

    PlugboardDecryptInfo& operator=(const PlugboardDecryptInfo& other);

    ~PlugboardDecryptInfo(); // default
};


#endif //ENIGMA_PLUGBOARDDECRYPTINFO_H
