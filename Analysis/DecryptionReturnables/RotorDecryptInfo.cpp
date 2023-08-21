//
// Created by aaron on 2023-06-24.
//

#include <iostream>
#include <iomanip>
#include "RotorDecryptInfo.h"

RotorDecryptInfo::RotorDecryptInfo(): DecryptInfo(), reflector {}, method {}{
    rotors = new int[3]{};
    rotor_pos = new int[3]{};
}

RotorDecryptInfo::RotorDecryptInfo(int* new_rotors, int* new_rotor_pos, char ref, stdo::Method new_method, long double new_fitness):
        DecryptInfo(new_fitness), reflector {ref}, method {new_method}
{
    rotors = new int[3]{};
    stdo::arrncpy(rotors, new_rotors, 3);

    rotor_pos = new int[3];
    stdo::arrncpy(rotor_pos, new_rotor_pos, 3);
}

RotorDecryptInfo::RotorDecryptInfo(const RotorDecryptInfo& other): DecryptInfo(other.fitness){
    rotors = new int[3]{};
    rotor_pos = new int[3]{};
    stdo::arrncpy(rotors, other.rotors, 3);
    stdo::arrncpy(rotor_pos, other.rotor_pos, 3);
    reflector = other.reflector;
    method = other.method;
}

RotorDecryptInfo& RotorDecryptInfo::operator=(const RotorDecryptInfo& other){
    if(this == &other){ return *this; } // self assignment guard
    stdo::arrncpy(rotors, other.rotors, 3);
    stdo::arrncpy(rotor_pos, other.rotor_pos, 3);
    reflector = other.reflector;
    method = other.method;
    fitness = other.fitness;
    return *this;
}

RotorDecryptInfo::~RotorDecryptInfo(){
    delete[] rotors;
    delete[] rotor_pos;
}

void RotorDecryptInfo::print(bool header) const{
    using namespace std;
    using namespace stdo;

    if(header){
        cout << "ROTORS:           POSITIONS:       REFLECTOR:       FITNESS:" << endl;
    }
    for(int i {}; i < 3; i++){
        cout << left << setw(4) << itor(rotors[i]);
    }
    cout << "  |   ";
    for(int i {}; i < 3; i++){
        cout << left << setw(4) << rotor_pos[i];
    }
    cout << " |   ";
    cout << static_cast<char>(toupper(reflector)) << "          |     "  << fitness << endl;
}

void RotorDecryptInfo::print() const{
    print(false);
}

[[nodiscard]] EnigmaConfig RotorDecryptInfo::to_config() const{
    int rings[3] {0, 0, 0};
    return {rotors,
            rotor_pos,
            rings,
            reflector,
            ""
            };
}


void RotorDecryptInfo::to_config(EnigmaConfig& config) const{
    config = to_config();
}
