//
// Created by aaron on 2023-06-24.
//

#include "PlugboardDecryptInfo.h"

#include <utility>

PlugboardDecryptInfo::PlugboardDecryptInfo(): plugboard {}, method {}, fitness {0}{
    ring_info = *new RingDecryptInfo{};
}

PlugboardDecryptInfo::PlugboardDecryptInfo(const RingDecryptInfo& rinfo, std::string new_plugboard,
                                           Op::Method new_method, long double new_fitness):
                                                ring_info {rinfo}, plugboard {std::move(new_plugboard)},
                                                method {new_method}, fitness {new_fitness}
{ }

PlugboardDecryptInfo::PlugboardDecryptInfo(const PlugboardDecryptInfo& other){
    ring_info = other.ring_info;
    plugboard = other.plugboard;
    method = other.method;
    fitness = other.fitness;
}

PlugboardDecryptInfo& PlugboardDecryptInfo::operator=(const PlugboardDecryptInfo& other){
    if(this == &other) { return *this; } // self assignment guard
    ring_info = other.ring_info;
    plugboard = other.plugboard;
    method = other.method;
    fitness = other.fitness;
    return *this;
}


PlugboardDecryptInfo::~PlugboardDecryptInfo() = default;