//
// Created by aaron on 2023-06-24.
//

#include <iostream>
#include <iomanip>
#include "RotorDecryptInfo.h"

// default constructor
RotorDecryptInfo::RotorDecryptInfo(): DecryptInfo(), reflector {}, method {}{
    rotors = new int[3]{};
    rotor_pos = new int[3]{};
}

RotorDecryptInfo::RotorDecryptInfo(int* new_rotors, int* new_rotor_pos, char ref, Op::Method new_method, long double new_fitness):
        DecryptInfo(new_fitness), reflector {ref}, method {new_method}
{
    rotors = new int[3]{};
    Op::rep_arr(rotors, new_rotors, 3);

    rotor_pos = new int[3];
    Op::rep_arr(rotor_pos, new_rotor_pos, 3);
}

// copy constructor
RotorDecryptInfo::RotorDecryptInfo(const RotorDecryptInfo& other): DecryptInfo(other.fitness){
    rotors = new int[3]{};
    rotor_pos = new int[3]{};
    Op::rep_arr(rotors, other.rotors, 3);
    Op::rep_arr(rotor_pos, other.rotor_pos, 3);
    reflector = other.reflector;
    method = other.method;
}

// copy assignment operator
RotorDecryptInfo& RotorDecryptInfo::operator=(const RotorDecryptInfo& other){
    if(this == &other){ return *this; } // self assignment guard
    Op::rep_arr(rotors, other.rotors, 3);
    Op::rep_arr(rotor_pos, other.rotor_pos, 3);
    reflector = other.reflector;
    method = other.method;
    fitness = other.fitness;
    return *this;
}

// destructor
RotorDecryptInfo::~RotorDecryptInfo(){
    delete[] rotors;
    delete[] rotor_pos;
}

void RotorDecryptInfo::print(bool header) const{
    using namespace std;
    using namespace Op;
    if(header){
        cout << "ROTOR SETTINGS:" << endl;
        for(int i{}; i < 3; i++){
            cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "     ";
        }
        cout << "REF" << "          " << "FITNESS" << endl;
    }
    cout << left << setw(3) << itor(rotors[0]) << "  " << left << setw(2) << rotor_pos[0] << "  |  "
         << left << setw(3) << itor(rotors[1]) << "  " << left << setw(2) << rotor_pos[1] << "  |  "
         << left << setw(3) << itor(rotors[2]) << "  " << left << setw(2) << rotor_pos[2] << "  |  "
         << "REF: " << static_cast<char>(toupper(reflector)) << "  "
         << " ->  " << fitness << endl;
}

void RotorDecryptInfo::print() const{
    print(false);
}

EnigmaConfig RotorDecryptInfo::to_config(){
    int rings[3] {0, 0, 0};
    return {rotors,
            rotor_pos,
            rings,
            reflector,
            ""
            };
}


void RotorDecryptInfo::to_config(EnigmaConfig& config){
    config = to_config();
}