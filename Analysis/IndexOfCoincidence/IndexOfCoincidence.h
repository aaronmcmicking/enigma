//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_INDEXOFCOINCIDENCE_H
#define ENIGMA_INDEXOFCOINCIDENCE_H

#define MAX_BUFFER_LENGTH (40*1000) // 40k prevents value overflow in summations

#define NORMALIZING_COEFFICIENT 26

#include <string>
#include "../Ops.h"

class IndexOfCoincidence {
public:
    static long double calculate(const std::string& filename);
};


#endif //ENIGMA_INDEXOFCOINCIDENCE_H
