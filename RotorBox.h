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

    Rotor* rotors_in_place {new Rotor[3]{}};

public:
    RotorBox();

    Rotor get_rotor(int rotor_number);

    Rotor* get_all_rotors();

    void set_placed_rotor(int rotor_number, int position);

    char convert_char(char c);

    [[nodiscard]] Rotor* get_rotors_in_place();

    static int ctoi(char c);

    static char itoc(int i);

    static int reflect(int input);
};

#endif //ENIGMA_ROTORBOX_H
