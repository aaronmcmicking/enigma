//
// Created by aaron on 2023-06-24.
//

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