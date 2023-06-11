//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_OPS_H
#define ENIGMA_OPS_H

#include <iostream>
#include <fstream>

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

#ifndef uint
#define uint unsigned int
#endif

class Ops {
public:
    static int ctoi(char c);

    static char itoc(int i);

    static void rep_arr3(int dest[3], int a, int b, int c);

    static void rep_arr3(int dest[3], const int *src);

    static void rep_arr3(char dest[3], const char *src);

    static void rep_arr(int* dest, const int* src, int size);

    static void rep_arr(char* dest, const char* src, int size);

    static void format_input_file(const std::string &filename);

    static std::string format_text(const std::string &str);

    // allocates, but DOES NOT deallocate memory
    static char* load_from_file(const std::string& filename, int* size);

};


#endif //ENIGMA_OPS_H
