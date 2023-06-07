//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTOR_H
#define ENIGMA_ROTOR_H

#define CONVERSION_MAP_ARRAY_SIZE 27

class Rotor {
private:
    int position;

    void fill_default_mappings();

public:
    static const int max_position {26};
    static const int min_position {1};
    int ring_position;
    bool turnover_flag {false}; // true if the next rotor should turn, false otherwise
    int mappings[CONVERSION_MAP_ARRAY_SIZE]; // 1-indexed (ignore position 0)

    Rotor();

    Rotor(int initial_position, int ring_pos);

    Rotor(int initial_position, int ring_pos, const int map[CONVERSION_MAP_ARRAY_SIZE]);

    [[nodiscard]] int get_position() const;

    [[nodiscard]] int get_ring_position() const;

    void set_ring_position(int new_ring_position);

    void set_position(int new_pos);

    void set_mappings(const int new_mappings[CONVERSION_MAP_ARRAY_SIZE]);

    int next(int normalized_input, bool forward, bool should_rotate);

    [[nodiscard]] bool next_should_turn() const;

    void reset_turnover_flag();

    void print_rotor_mappings() const;
};


#endif //ENIGMA_ROTOR_H
