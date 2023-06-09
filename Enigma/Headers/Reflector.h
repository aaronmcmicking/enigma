//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_REFLECTOR_H
#define ENIGMA_REFLECTOR_H


#include "EMOps.h"
#include "Rotor.h"

class Reflector {
public:
    Reflector();

    explicit Reflector(char c);

    void set_reflector(char c);

    void set_reflector(Reflector r);

    int reflect(int input);

private:
    int* mapping;

    static int* get_mapping(char c);
};


#endif //ENIGMA_REFLECTOR_H