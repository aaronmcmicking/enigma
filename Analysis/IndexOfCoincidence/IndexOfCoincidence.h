//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_INDEXOFCOINCIDENCE_H
#define ENIGMA_INDEXOFCOINCIDENCE_H

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

#include <string>

class IndexOfCoincidence {
private:
    static long double abs(long double val);

public:
    constexpr static const long double ENGLISH_EXPECTED_IOC {1.73};

    static const int NORMALIZING_COEFFICIENT {26};

    static long double calculate_f(const std::string& filename);

    static long double calculate(const char* text, int size);
};


#endif //ENIGMA_INDEXOFCOINCIDENCE_H
