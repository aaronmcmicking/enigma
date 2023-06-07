//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_INDEXOFCOINCIDENCE_H
#define ENIGMA_INDEXOFCOINCIDENCE_H

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

#include <string>
#include "../Ops.h"

class IndexOfCoincidence {
public:
    static const int NORMALIZING_COEFFICIENT {26};

    static long double calculate_f(const std::string& filename);

    static long double calculate(const char* text);
};


#endif //ENIGMA_INDEXOFCOINCIDENCE_H
