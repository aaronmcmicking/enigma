//
// Created by aaron on 2023-06-26.
//

#ifndef ENIGMA_ENIGMACONFIG_H
#define ENIGMA_ENIGMACONFIG_H

#include <iostream>
#include <string>

class EnigmaConfig{
public:
    int* rotors;
    int* rotor_pos;
    int* ring_pos;
    char reflector;
    std::string plugboard;

    EnigmaConfig();

    EnigmaConfig(int* n_rotors, int* n_rotor_pos, int* n_ring_pos, char n_reflector, std::string n_plugboard);

    EnigmaConfig(const EnigmaConfig& other);

    ~EnigmaConfig();

    EnigmaConfig& operator=(const EnigmaConfig& other);

    void print() const; // wraps print(*this)
    static void print(const EnigmaConfig& config);
};


#endif //ENIGMA_ENIGMACONFIG_H
