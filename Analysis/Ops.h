//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_OPS_H
#define ENIGMA_OPS_H

#include <iostream>
#include <fstream>

#define MAX_INPUT_STRING_LENGTH (40*1000)

void format_input_file(const std::string& filename);

void rep_arr3(int dest[3], const int* src);

void rep_arr3(int dest[3], int a, int b, int c);

std::string format_text(const std::string& str);

#ifndef ENIGMA_OPS_H
int ctoi(char c);

char itoc(int i);
#endif

// -----------------------------------------------------

#ifdef OPS_IMPLEMENTATION



#endif // OPS_IMPLEMENTATION

#endif //ENIGMA_OPS_H
