//
// Created by aaron on 2023-06-03.
//

#ifndef ENIGMA_PLUGBOARD_H
#define ENIGMA_PLUGBOARD_H

#include <string>

struct InvalidPlugboardStringException{
    std::string plugboard_string;
    std::string message;
};

class Plugboard {
private:
    /* pairs has 27 actual elements and 26 used elements with 1-based indexing. Index 0 is ignored and considered
     * invalid to access.
     * Every pair appears twice for each index of pair members. Inputs not mapped to a pair output themselves.
     * Has structure:
     * input: [output]
     * 0: [NULL] -> index 0 is considered invalid
     * 1: [5]
     * 2: [2]
     * 3: [25]
     * 4: [23]
     * 5: [1]
     * (...): []
     * 22: [22]
     * 23: [4]
     * 24: [24]
     * 25: [3]
     * 26: [26]
     */
    int* pairs;

    [[nodiscard]] static bool validate_plugboard_string(const std::string& str);

    void parse_and_set_pairs(std::string& str);

    int* without_dupes();

public:
    Plugboard(); // every input outputs itself

    explicit Plugboard(const std::string& pairs_str); // string -> "AF HG IK OJ MP VB" -> pairs A->F, H-G, etc and vice-versa

    void set_pairs(const std::string& new_pairs);

    std::string get_pairs(); // returns string of pairs in same format as set_pairs and constructor takes int

    int convert_int(int i);

    int convert_char(char c); // wrapper for convert_int(int c)

    int num_pairs();

    static int num_pairs(const std::string& pair_str);

    void print();

    // returns true if the new_pair is allowed to be added, false otherwise
    static bool can_add(const std::string& new_pair, const int* pairs);

    static bool can_add(const std::string& new_pair, const std::string& pairs);
};


#endif //ENIGMA_PLUGBOARD_H
