//
// Created by aaron on 2023-06-06.
//

#include <fstream>
#include <iostream>
#include <chrono>
#include "IndexOfCoincidence.h"

long double IndexOfCoincidence::calculate_f(const std::string &filename) {
    stdo::format_input_file(filename);

    char buf[MAX_INPUT_STRING_LENGTH] {0};
    std::ifstream file {filename};
    file.get(buf, MAX_INPUT_STRING_LENGTH);
    int size {static_cast<int>(file.gcount())};
    return calculate(buf, size);
}

long double IndexOfCoincidence::calculate(const char* text, int size){
//    auto start_time = std::chrono::high_resolution_clock::now();
    int appearances[27] {0};

    for(int i {0}; text[i] != '\0' && i < size; i++){
        appearances[text[i] - 'a' + 1] += 1; // ignoring safety checks is ~20-25% faster
    }

    unsigned long long sum {};
    for(int i {1}; i < 27; i++){
        int val {appearances[i]};
        sum += val*(val-1);
    }

    size--; // -1 to account for null terminator in c-string
    long double den = size*(size-1) / static_cast<long double>(NORMALIZING_COEFFICIENT);
    long double measured_ioc = sum / den;

//    auto end_time = std::chrono::high_resolution_clock::now();
//    auto duration = duration_cast<std::chrono::nanoseconds>(end_time - start_time);
//    std::cout << std::endl << "IOC took " << duration.count() << " nanoseconds" << std::endl;

    return 1 - stdo::abs(ENGLISH_EXPECTED_IOC - measured_ioc);
//    return measured_ioc;
}