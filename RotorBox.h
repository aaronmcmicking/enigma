//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORBOX_H
#define ENIGMA_ROTORBOX_H


#include "Rotor.h"

class RotorBox {
private:

    // the rotors
    Rotor RotorI {};
    Rotor RotorII {};
    Rotor RotorIII {};
    Rotor RotorIV {};
    Rotor RotorV {};
    Rotor RotorVI {};
    Rotor RotorVII {};
    Rotor RotorVIII {};

    Rotor* rotors_in_place {nullptr};

public:
    RotorBox();

    Rotor get_rotor(int rotor_number);

    Rotor* get_all_rotors();

    void set_placed_rotor(int rotor_number, int position);
};

#endif //ENIGMA_ROTORBOX_H
