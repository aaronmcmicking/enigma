//
// Created by aaron on 2023-06-03.
//

#ifndef ENIGMA_PLUGBOARD_H
#define ENIGMA_PLUGBOARD_H

#include <string>

/*
 * The plugboard allows two characters to be 'swapped' in pairs. Ten such pairs can be connected at any given time. This
 * conversion is done before and after an input/output interacts with the rotors.
 *
 * Similar to rotors and reflectors, the paired characters are stored in as their 1-index in the alphabet in `pairs`.
 *
 * The current pairs can be set using a string with desired pairs listed adjacent. By convention, this string
 * is formatted as "AD IJ BT WR" in usages. However, the parser will accept any string as long as:
 *  1. the string contains an even number of characters
 *  2. a character is not used more than once
 * As a result, a character may also not be paired to itself. As well, the parser ignores case, whitespace and
 * non-alphabetical characters.
 */
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

    /*
     * Validates that `str` contains a valid plugboard configuration.
     */
    [[nodiscard]] static bool validate_plugboard_string(const std::string& str);

    /*
     * Parses and applies the plugboard pairs in `str`. Invokes `validate_plugboard_string()`.
     */
    void parse_and_set_pairs(std::string& str);

    /*
     * Returns a duplicate of `pairs` with entries zero-ed such that a given pair appears only once (see documentation for
     * `pairs`). Used to format the current plugboard for printing/readability.
     */
    int* without_dupes();

public:
    // every input outputs itself by default
    Plugboard();

    explicit Plugboard(const std::string& pairs_str); // string -> "AF HG IK OJ MP VB" -> pairs A->F, H-G, etc and vice-versa

    // Sets the current configuration to that specified in `new_pairs`. If the input is not a valid configuration, the
    // current configuration is not modified.
    void set_pairs(const std::string& new_pairs);

    // Returns a string of pairs in same format as set_pairs and constructor takes int
    std::string get_pairs();

    // Converts an integer according to the current plugboard configuration. If
    int convert_int(int i);

    // wrapper for convert_int(int i)
    int convert_char(char c);

    // Returns the number of pairs currently set
    int num_pairs();

    // Returns the number of pairs contained in `pair_str`
    static int num_pairs(const std::string& pair_str);

    // Prints the current plugboard configuration. `show_default_connections` is true if values not included in any
    // pair should be printed
    void print(bool show_default_connections);

    // Returns true if the given pair can be added to the current plugboard, false otherwise
    bool can_add(const std::string& new_pair);

    // returns true if the `new_pair` is allowed to be added to `pairs`, false otherwise
    // Here, `pairs` is an int-array in the same format as used during conversions (such that the pair for the nth
    // letter of the alphabet is at pairs[n])
    static bool can_add(const std::string& new_pair, const int* pairs);

    // returns true if the `new_pair` is allowed to be added to `pairs`, false otherwise
    // Here, `pairs` is a string in the same format as used when setting a new plugboard configuration
    static bool can_add(const std::string& new_pair, const std::string& pairs);
};


#endif //ENIGMA_PLUGBOARD_H
