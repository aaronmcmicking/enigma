//
// Created by aaron on 2023-06-24.
//

#include <iostream>
#include <iomanip>
#include "RingDecryptInfo.h"

RingDecryptInfo::RingDecryptInfo(): method {}, fitness {0}{
    rotor_info = *new RotorDecryptInfo {};
    ring_pos = new int[3]{};
}

RingDecryptInfo::RingDecryptInfo(const RotorDecryptInfo& rinfo, int* new_ring_pos, Op::Method new_method,
                                 long double new_fitness):
                                 rotor_info {rinfo}, method {new_method}, fitness {new_fitness}
{
    ring_pos = new int[3]{};
    Op::rep_arr(ring_pos, new_ring_pos, 3);
}

RingDecryptInfo::RingDecryptInfo(const RingDecryptInfo &other):
            rotor_info {other.rotor_info}, method {other.method}, fitness {other.fitness}
{
    ring_pos = new int[3]{};
    Op::rep_arr(ring_pos, other.ring_pos, 3);
}

RingDecryptInfo& RingDecryptInfo::operator=(const RingDecryptInfo& other){
    if(this == &other){ return *this; } // self assignment guard
    rotor_info = other.rotor_info;
    Op::rep_arr(ring_pos, other.ring_pos, 3);
    method = other.method;
    fitness= other.fitness;
    return *this;
}

RingDecryptInfo::~RingDecryptInfo(){
     delete[] ring_pos;
}

void RingDecryptInfo::print(bool header) const{
    using namespace std;
    using namespace Op;
    if(header){
        cout << "RING SETTINGS:" << endl;
        for(int i{}; i < 3; i++)
            cout << left << setw(3) << "R" << "  " << setw(2) << "P" << "  " << "RING" << "        ";
        cout << "REF" << "          " << "FITNESS" << endl;
    }
    cout << left << setw(3) << itor( rotor_info.rotors[0]) << "  " << setw(2) <<  rotor_info.rotor_pos[0] << "  ring: " << setw(2) <<  ring_pos[0] << " |  "
        << left << setw(3) << itor( rotor_info.rotors[1]) << "  " << setw(2) <<  rotor_info.rotor_pos[1] << "  ring: " << setw(2) <<  ring_pos[1] << " |  "
        << left << setw(3) << itor( rotor_info.rotors[2]) << "  " << setw(2) <<  rotor_info.rotor_pos[2] << "  ring: " << setw(2) <<  ring_pos[2] << " |  "
        << "REF: " << static_cast<char>(toupper( rotor_info.reflector)) << "  "
        << " ->  " <<  fitness << endl;
}

void RingDecryptInfo::print() const{
    print(false);
}