//
// Created by aaron on 2023-06-24.
//

#include <iostream>
#include "RotorDecryptInfo.h"

// default constructor
RotorDecryptInfo::RotorDecryptInfo(): reflector {}, method {}, fitness {}{
    rotors = new int[3]{};
    rotor_pos = new int[3]{};
}

RotorDecryptInfo::RotorDecryptInfo(int* new_rotors, int* new_rotor_pos, char ref, Op::Method new_method, long double new_fitness):
        rotors {new_rotors}, rotor_pos {new_rotor_pos}, reflector {ref}, method {new_method}, fitness {new_fitness}
{ }

// copy constructor
RotorDecryptInfo::RotorDecryptInfo(const RotorDecryptInfo& other){
    rotors = new int[3]{};
    rotor_pos = new int[3]{};
    Op::rep_arr(rotors, other.rotors, 3);
    Op::rep_arr(rotor_pos, other.rotor_pos, 3);
    reflector = other.reflector;
    method = other.method;
    fitness = other.fitness;
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