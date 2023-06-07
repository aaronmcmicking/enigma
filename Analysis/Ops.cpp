//
// Created by aaron on 2023-06-06.
//

#include "Ops.h"

void format_input_file(const std::string& filename){
    std::ifstream ifile {filename};

    char buf[MAX_INPUT_STRING_LENGTH] {};

    ifile.read(buf, MAX_INPUT_STRING_LENGTH);
    ifile.close();
    std::remove(filename.c_str());

    std::string buf2 = format_text(buf);

    std::ofstream ofile {filename};
    ofile << buf2;
    ofile.close();
}

void rep_arr3(int dest[3], const int* src){
    for(int i {0}; i < 3; i++) dest[i] = src[i];
}

void rep_arr3(int dest[3], int a, int b, int c){
    int src[] {a, b, c};
    rep_arr3(dest, src);
}

#ifndef ENIGMA_EMOPS_H

std::string format_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

int ctoi(char c) {
    return static_cast<int>(c - 'a' + 1);
}

char itoc(int i) {
    return static_cast<char>(i + 'a' - 1);
}
#endif // ENIGMA_EMOPS_H