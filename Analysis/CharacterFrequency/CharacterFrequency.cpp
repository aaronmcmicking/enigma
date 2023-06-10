//
// Created by aaron on 2023-06-10.
//

#include <iostream>
#include "CharacterFrequency.h"

double CharacterFrequency::calculate(const char* text, int size){

//    std::cout << "size = " << size << std::endl;

    int appearances[27] {};

    for(int i {0}; text[i] != '\0' && i < size; i++){
        appearances[text[i] - 'a' + 1] += 1;
    }

//    std::cout << "m_freq = {";
    double m_freq[27];
    double count {static_cast<double>(size-1)};
    for(int i {1}; i <= 26; i++){
        m_freq[i] = appearances[i] / count;
//        std::cout << m_freq[i] << ", ";
    }
//    std::cout << "}" << std::endl;

//    std::cout << "expect = {";
//    for(int i {1}; i <= 26; i++){
//        std::cout << expected[i] << ", ";
//    }
//    std::cout << "}" << std::endl;

    double sum {0.0};
    for(int i {1}; i <= 26; i++){
        sum += abs(m_freq[i] - expected[i]);
    }

    return 1 - sum;
//    return sum / 26.0;
}

double CharacterFrequency::abs(double val){
    return val >= 0.0 ? val : -val;
}