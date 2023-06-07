//
// Created by aaron on 2023-06-06.
//

#include <fstream>
#include <iostream>
#include "IndexOfCoincidence.h"
#include "..\Ops.h"

long double IndexOfCoincidence::calculate(const std::string& filename){
    Ops::format_input_file(filename);

    char buf[MAX_BUFFER_LENGTH] {0};
    std::ifstream file {filename};
    file.read(buf, MAX_BUFFER_LENGTH-1);

    int appearances[27] {0};

    int count {0};
    for(int i {1}; buf[i] != 0; i++){
        count++;
        int c {Ops::ctoi(buf[i])};
        if(c < 1 || c > 26) std::cout << "BAD INDEX (" << c << ")" << std::endl;
        else appearances[Ops::ctoi(buf[i])] += 1;
    }

    std::cout << "count = " << count << std::endl;

    unsigned long long sum {};
    for(int i {1}; i < 27; i++){
        int val {appearances[i]};
        sum += val*(val-1);
    }

    long double den = count*(count-1) / static_cast<long double>(NORMALIZING_COEFFICIENT);
    long double returnable = sum / den;

    if(returnable < -0.01 || returnable > 5){
        std::cout << "INDEX_OF_COINCIDENCE ERROR FOR FINAL VALUE" << returnable << std::endl;
    }

    return returnable;
}
