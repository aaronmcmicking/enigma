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

void PlugboardDecryptInfo::print(bool header) const {
    using namespace std;
    using namespace Op;

    if(header){
        for(int i{}; i < 3; i++){
            cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "  " << "RING" << "        ";
        }
        cout << "REF" << "          " << "FITNESS" << endl;
    }

    cout << left << setw(3) << itor(ring_info.rotor_info.rotors[0]) << "  " << setw(2) << ring_info.rotor_info.rotor_pos[0] << "  ring: " << setw(2) << ring_info.ring_pos[0] << " |  "
         << left << setw(3) << itor(ring_info.rotor_info.rotors[1]) << "  " << setw(2) << ring_info.rotor_info.rotor_pos[1] << "  ring: " << setw(2) << ring_info.ring_pos[1] << " |  "
         << left << setw(3) << itor(ring_info.rotor_info.rotors[2]) << "  " << setw(2) << ring_info.rotor_info.rotor_pos[2] << "  ring: " << setw(2) << ring_info.ring_pos[2] << " |  "
         << "REF: " << static_cast<char>(toupper(ring_info.rotor_info.reflector)) << "  "
         << " ->  " << fitness << endl;
    cout << "WITH PLUGBOARD: " << plugboard << endl;
}

void PlugboardDecryptInfo::print() const{
    print(false);
}