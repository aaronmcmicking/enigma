//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_EMOPS_H
#define ENIGMA_EMOPS_H

#include <utility>
#include <string>

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

#ifndef uint
#define uint uint32_t
#endif

/*
 * Contains common operations throughout EnigmaMachine for convenience.
 */
class EMOps { // "EMOps" = Enigma Machine Operations
public:
    // Converts a letter into its 1-indexed position in the alphabet (ie. 'a' -> 1, 'c' -> 3, `z` -> 26, etc.)
    static int ctoi(char c);

    // Converts a letter from its 1-indexed position in the alphabet to its lowercase integer representation
    // (ie. 3 -> 'c', 25 -> 'y', etc.)
    static char itoc(int i);

    // Returns true if  min <= num <= max,  false otherwise
    static bool is_in_range(int num, int min, int max);

    // Returns string of lowercase version of all alphabetical characters in `str`
    // ie. "KM47 ==- 1294 H7HY';235"  -->  "kmhhy"
    static std::string strip_text(const std::string& str);

    // Copies first three vales of `src` into `dest`
    static void rep_arr3(int dest[3], const int* src);

    // Copies {a, b, c} into `dest`
    static void rep_arr3(int dest[3], int a, int b, int c);
};


#endif //ENIGMA_EMOPS_H
