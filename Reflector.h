//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_REFLECTOR_H
#define ENIGMA_REFLECTOR_H


#include <map>
#include "Operations.h"

class Reflector {
public:
    Reflector();

    explicit Reflector(char c);

    void set_reflector(char c);

    int reflect(int in);

private:
    std::map<int, int> mapping;

    static std::map<int, int> get_mapping(char c);
};


#endif //ENIGMA_REFLECTOR_H
