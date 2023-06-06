//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORBOX_H
#define ENIGMA_ROTORBOX_H


#include "Rotor.h"
#include "Reflector.h"

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

    Reflector reflector {};

public:
    RotorBox();

    Rotor get_rotor(int rotor_number);

    Rotor* get_all_rotors();

    void set_placed_rotor(int rotor_number, int position);

    void set_placed_rotor(const int* rotors);

    void set_placed_rotor(int* rotors, int* pos);

    int convert_int(int i);

    int reflect(int input);

    [[nodiscard]] Rotor* get_rotors_in_place();

    // returns pointer to the rotor array (rotors are stored by value)
    Rotor* set_rotor_pos(int rotor_pos, int pos);

    // returns pointer to the rotor array (rotors are stored by value)
    Rotor* set_rotor_pos(const int pos[3]);

    void set_reflector(char c);

    Reflector get_reflector();
};

#endif //ENIGMA_ROTORBOX_H
