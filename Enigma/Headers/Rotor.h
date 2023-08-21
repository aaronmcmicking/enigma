//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTOR_H
#define ENIGMA_ROTOR_H

// The number of characters in an array that stores rotor, plugboard, etc. conversion maps. Index 0 is ignored (set to 0)
// and indexes 1-27 stores conversions. An input is considered an index and the output is the value at that input index.
#define CONVERSION_MAP_ARRAY_SIZE 27

/*
 * See https://en.wikipedia.org/wiki/Enigma_machine for more information.
 *
 * A rotor consists of set of a hardcoded conversion map and a ring position which, when the rotor is placed in sequence
 * with other rotors, controls whether the next rotor in the sequence should turn.
 *
 * Rotor mappings are the same as used in genuine Enigma machines, sourced from https://en.wikipedia.org/wiki/Enigma_rotor_details.
 * There are five rotors fully implemented: I, II, III, IV, V, and three partially implemented: VI, VII, VIII. The
 * real-life counterparts of the three partially implemented rotors were later additions to the Enigma Machine and had two
 * ring positions that could rotate a following rotor. These second notch positions have not been implemented and the rotors
 * are treated to have one notch.
 *
 * Similar to rotors and the plugboard, characters are represented in the map as their 1-index position in the English
 * alphabet rather than their integer representation. ie., mapping[1] == 'A', mapping[2] == 'B', etc.
 */
class Rotor {
private:
    int position; // current rotor position. Always 1 <= position <= 26

    void fill_default_mappings(); // fills such that an output will be its input (no conversion)

public:
    static const int max_position {26};
    static const int min_position {1};
    int ring_position; //  the position of the notch which controls whether the next rotor in a sequence of rotors should rotate
    bool turnover_flag {false}; // true if the next rotor should turn, false otherwise
    int forward_mapping[CONVERSION_MAP_ARRAY_SIZE]; // conversion map when travelling forward through the rotor
    int reverse_mapping[CONVERSION_MAP_ARRAY_SIZE]; // conversion map when travelling backwards through the rotor

    // initializes to a rotor which simply "passes through" any input value (output = input)
    Rotor();

    // `map` is treated to contain the forward conversions and is reversed to create `reverse_mapping`
    Rotor(int initial_position, int ring_pos, const int map[CONVERSION_MAP_ARRAY_SIZE]);

    [[nodiscard]] int get_position() const;

    [[nodiscard]] int get_ring_position() const;

    void set_ring_position(int new_ring_position);

    void set_position(int new_pos);

    // `new_mapping` is treated to contain only the forward map and is reversed to generate `reverse_mapping`
    void set_mappings(const int new_mapping[CONVERSION_MAP_ARRAY_SIZE]);

    /**
     * Converts a input to an output and decides whether the next rotor in sequence (if applicable) should rotate
     * @param normalized_input The input position relative to the 0-position of the rotor. If this is position n, then
     * the associated character at that position MAY NOT be the nth letter of the alphabet
     * @param forward True if the input is passing forward through the rotor, false otherwise
     * @param should_rotate True if this rotor should rotate before converting the input
     * @return The normalized output which is suitable as input for the next rotor
     */
    int next(int normalized_input, bool forward, bool should_rotate);

    // returns true if the next rotor in sequence should rotate, false otherwise
    [[nodiscard]] bool should_next_turn() const;

    // resets turnover_flag to false
    void reset_turnover_flag();

    // returns and resets the turnover flag (wrapper collapses multiple function calls)
    [[nodiscard]] bool pop_turnover_flag();

    void print_rotor_mappings() const;
};


#endif //ENIGMA_ROTOR_H
