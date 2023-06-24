//
// Created by aaron on 2023-06-10.
//

#include "CharacterFrequency.h"

double CharacterFrequency::calculate(const char* text, int size){
    int appearances[27] {};

    for(int i {0}; text[i] != '\0' && i < size; i++){
        appearances[text[i] - 'a' + 1] += 1;
    }

    double m_freq[27];
    double count {static_cast<double>(size-1)};
    for(int i {1}; i <= 26; i++){
        m_freq[i] = appearances[i] / count;
    }

    double sum {0.0};
    for(int i {1}; i <= 26; i++){
        sum += Op::abs(m_freq[i] - expected[i]);
    }

    return 1 - sum;
}