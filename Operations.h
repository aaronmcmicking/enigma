//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_OPERATIONS_H
#define ENIGMA_OPERATIONS_H

#include <utility>

/*
 * Helper class that contains general operations relating to character-int conversions and map operations *
 */

class Operations {
public:
    static int ctoi(char c);

    static char itoc(int i);

    static bool is_in_range(int num, int min, int max);

//    static void map_insert(std::map<int, int>& map, int k, char v);

    static std::string strip_text(const std::string& str);

//    static std::pair<int, int> pair(int k, int v);
};


#endif //ENIGMA_OPERATIONS_H
