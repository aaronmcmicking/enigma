//
// Created by aaron on 2023-06-05.
//

#ifndef ENIGMA_ENIGMAMACHINE_H
#define ENIGMA_ENIGMAMACHINE_H


#include "RotorBox.h"
#include "Plugboard.h"

class EnigmaMachine {
private:
    RotorBox rotor_box;
    Plugboard plugboard;

    EnigmaMachine(); // may not be instantiated without proper fields

    int convert_char(char c);
public:
    EnigmaMachine(int rotors[3], int rotor_pos[3], char reflector, const std::string& plugboard);

    std::string encrypt_or_decrypt(const std::string& in);

    bool encrypt_or_decrypt_file(const std::string& in_file_name, const std::string& out_file_name); // true if success, false otherwise

    void set_rotor_pos(const int* pos);

    void set_reflector(char c);

    void set_plugboard_settings(const std::string& settings);

    void print_settings();
};


#endif //ENIGMA_ENIGMAMACHINE_H
