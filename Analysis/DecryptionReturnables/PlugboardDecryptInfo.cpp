//
// Created by aaron on 2023-06-24.
//

#include "PlugboardDecryptInfo.h"

#include <utility>

PlugboardDecryptInfo::PlugboardDecryptInfo(): DecryptInfo(), plugboard {}, method {}{
    ring_info = *new RingDecryptInfo{};
}

PlugboardDecryptInfo::PlugboardDecryptInfo(const RingDecryptInfo& rinfo, std::string new_plugboard,
                                           stdo::Method new_method, long double new_fitness):
                                                DecryptInfo(new_fitness), ring_info {rinfo},
                                                plugboard {std::move(new_plugboard)}, method {new_method}
{ }

PlugboardDecryptInfo::PlugboardDecryptInfo(const PlugboardDecryptInfo& other): DecryptInfo(other.fitness){
    ring_info = other.ring_info;
    plugboard = other.plugboard;
    method = other.method;
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

void PlugboardDecryptInfo::print(bool header) const {
    using namespace std;
    using namespace stdo;

    ring_info.print(header);
    cout << "WITH PLUGBOARD: " << plugboard << endl;
}

void PlugboardDecryptInfo::print() const{
    print(false);
}

[[nodiscard]] EnigmaConfig PlugboardDecryptInfo::to_config() const{
    return {ring_info.rotor_info.rotors,
            ring_info.rotor_info.rotor_pos,
            ring_info.ring_pos,
            ring_info.rotor_info.reflector,
            plugboard
            };
}


void PlugboardDecryptInfo::to_config(EnigmaConfig& config) const{
    config = to_config();
}