//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_OPS_H
#define ENIGMA_OPS_H

#include <iostream>
#include <fstream>

#define MAX_INPUT_STRING_LENGTH (40*1000)

class Ops {
public:
    static void format_input_file(const std::string &filename);

    static void rep_arr3(int dest[3], const int *src);

    static void rep_arr3(int dest[3], int a, int b, int c);

    static std::string format_text(const std::string &str);

    static int ctoi(char c);

    static char itoc(int i);
};


#endif //ENIGMA_OPS_H
