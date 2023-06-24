//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORBOX_H
#define ENIGMA_ROTORBOX_H


#include <list>
#include "Rotor.h"
#include "Reflector.h"

/*
 * RotorBox encapsulates the current rotors and reflectors being used. Handles the behaviour of the rotors and reflector
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

    // the current reflector being used
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

    // Places a specific rotor in a specific position.
    // 1 <= rotor_number <= 8 and 1 <= position <= 26
    void set_rotor(int rotor_number, int position);

    // sets all the rotors (with default rotor positions) in the order they appear in `rotors`
    // `rotors` should have 3 elements
    void set_rotors(const int* rotors);

    // sets all the rotors in the order they appear in `rotors` and sets them to have the corresponding positions in `pos`
    void set_rotors(int* rotors, int* pos);

    // Returns an array of the three rotors currently installed in the rotor box, in order
    [[nodiscard]] Rotor* get_rotors_in_place();

    // Encrypts an integer through the rotors/reflector and returns its output
    int convert_int(int i);

    // returns pointer to the rotor array (rotors are stored by value)
    Rotor* set_rotor_pos(int rotor_pos, int pos);

    // returns pointer to the rotor array (rotors are stored by value)
    Rotor* set_rotor_pos(const int pos[3]);

    // Sets the ring position of the rotor in position `pos`
    Rotor* set_rotor_ring_pos(int ring_pos, int pos);

    // Sets all the ring positions of the installed rotors to the corresponding positions in `pos`
    Rotor* set_rotor_ring_pos(const int pos[3]);

    // Sets the reflector currently installed. `c` may be 'A', 'B', or 'C'
    void set_reflector(char c);

    // Sets the currently installed reflector to the reflector given
    void set_reflector(Reflector r);

    // Returns the currently installed reflector
    Reflector get_reflector();
};

#endif //ENIGMA_ROTORBOX_H
