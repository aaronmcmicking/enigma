//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_EMOPS_H
#define ENIGMA_EMOPS_H

#include <utility>
#include <string>

#define MAX_INPUT_STRING_LENGTH (100*1000)

/*
 * Helper class that contains general operations relating to character-int conversions and map operations *
 */

class EMOps { // "EMOps" = Enigma Machine Operations
public:
    static int ctoi(char c);

    static char itoc(int i);

    static bool is_in_range(int num, int min, int max);

    static std::string strip_text(const std::string& str);

};


#endif //ENIGMA_EMOPS_H