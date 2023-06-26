//
// Created by aaron on 2023-06-26.
//

#include <utility>

#include "Headers/EnigmaConfig.h"
#include "../Analysis/Op.h"

EnigmaConfig::EnigmaConfig(): reflector {'A'}, plugboard {}{
    rotors = new int[3]{1, 2, 3};
    rotor_pos = new int[3]{1, 1, 1};
    ring_pos = new int[3]{0, 0, 0}; // explicitly all zeroes
}

EnigmaConfig::EnigmaConfig(int* n_rotors, int* n_rotor_pos, int* n_ring_pos, char n_reflector, std::string n_plugboard)
                            : EnigmaConfig(){
    Op::rep_arr(rotors, n_rotors, 3);
    Op::rep_arr(rotor_pos, n_rotor_pos, 3);
    Op::rep_arr(ring_pos, n_ring_pos, 3);
    reflector = n_reflector;
    plugboard = std::move(n_plugboard);
}

EnigmaConfig::EnigmaConfig(const EnigmaConfig &other): EnigmaConfig(){
    rotors = other.rotors;
    rotor_pos = other.ring_pos;
    ring_pos = other.ring_pos;
    reflector = other.reflector;
    plugboard = other.plugboard;
}

EnigmaConfig::~EnigmaConfig(){
    delete[] rotors;
    delete[] rotor_pos;
    delete[] ring_pos;
}

EnigmaConfig &EnigmaConfig::operator=(const EnigmaConfig &other){
    if(this == &other){
        return *this;
    }
    Op::rep_arr(rotors, other.rotors, 3);
    Op::rep_arr(rotor_pos, other.rotor_pos, 3);
    Op::rep_arr(ring_pos, other.ring_pos, 3);
    reflector = other.reflector;
    plugboard = other.plugboard;
    return *this;
}

void EnigmaConfig::print() const{
    print(*this);
}

void EnigmaConfig::print(const EnigmaConfig& config){
    using namespace std;
    cout << "rotors = ";
    for(int i{}; i < 3; i++) {
        cout << config.rotors[i] << " ";
    }
    cout << endl << "pos = ";
    for(int i{}; i < 3; i++) {
        cout << config.rotor_pos[i] << " ";
    }
    cout << endl << "ref = " << config.reflector << endl;
    cout << "plugboard = " << config.plugboard << endl;
}
