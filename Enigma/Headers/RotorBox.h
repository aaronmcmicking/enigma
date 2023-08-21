//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORBOX_H
#define ENIGMA_ROTORBOX_H


#include <list>
#include "Rotor.h"
#include "Reflector.h"

/*
 * RotorBox contains the current rotors and reflectors being used. Handles the behaviour of the rotors and reflector
 * when encrypting a character (such as rotating rotors, etc)
 */
class RotorBox {
private:

    // the possible rotors
    Rotor RotorI {};
    Rotor RotorII {};
    Rotor RotorIII {};
    Rotor RotorIV {};
    Rotor RotorV {};
    Rotor RotorVI {};
    Rotor RotorVII {};
    Rotor RotorVIII {};

    // the current rotors being used
    Rotor* rotors_in_place {new Rotor[3]{}};

    Reflector reflector {};

    // reflects an integer through the reflector
    int reflect(int input);

public:
    /* The default (and only) constructor generates all the rotors and reflectors and inserts defaults rotors (I, II, III)
    * default reflector (A). Setting specific rotors/reflector must be done using individual function calls thereafter.
    */
    RotorBox();

    // Returns a specific rotor, regardless of if it is currently installed in the rotor box
    Rotor get_individual_rotor(int rotor_number);

    // Returns a list of all the possible rotors.
    std::list<Rotor> get_all_rotors();

    void set_rotor(int rotor_number, int position);

    void set_rotors(const int* rotors);

    // sets all the rotors in the order they appear in `rotors` and sets them to have the corresponding positions in `pos`
    void set_rotors(int* rotors, int* pos);

    [[nodiscard]] Rotor* get_rotors_in_place();

    // Encrypts an integer through the rotors/reflector and returns its output
    int convert_int(int i);

    // Sets the rotor position of the rotor in position `pos`
    Rotor* set_rotor_pos(int rotor_pos, int pos);

    // Sets all the rotor positions of the installed rotors to the corresponding positions in `pos`
    Rotor* set_rotor_pos(const int pos[3]);

    // Sets the ring position of the rotor in position `pos`
    Rotor* set_rotor_ring_pos(int ring_pos, int pos);

    // Sets all the ring positions of the installed rotors to the corresponding positions in `pos`
    Rotor* set_rotor_ring_pos(const int pos[3]);

    // Sets the reflector currently installed. `c` may be 'A', 'B', or 'C'
    void set_reflector(char c);

    void set_reflector(Reflector r);

    Reflector get_reflector();
};

#endif //ENIGMA_ROTORBOX_H
