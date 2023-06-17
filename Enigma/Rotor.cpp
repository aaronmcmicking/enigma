//
// Created by aaron on 2023-06-01.
//

#include <iostream>
#include "Headers/Rotor.h"
#include "Headers/EMOps.h"

void Rotor::fill_default_mappings(){
    for(int i {min_position}; i <= max_position; i++){
        forward_mapping[i] = i;
        reverse_mapping[i] = i;
    }
}

Rotor::Rotor(): position {min_position}, ring_position {max_position}, forward_mapping {}, reverse_mapping {} {
    fill_default_mappings();
}

Rotor::Rotor(int initial_position, int ring_pos): position {initial_position}, ring_position {ring_pos}, forward_mapping {}, reverse_mapping {} {
    fill_default_mappings();
}

Rotor::Rotor(int initial_position, int ring_pos, const int map[CONVERSION_MAP_ARRAY_SIZE])
        : position {initial_position}, ring_position {ring_pos}, forward_mapping {}, reverse_mapping {}
{
    set_mappings(map);
}

[[nodiscard]] int Rotor::get_position() const{
    return position;
}

[[nodiscard]] int Rotor::get_ring_position() const{
    return ring_position;
}

void Rotor::set_ring_position(int new_ring_position){
    if(EMOps::is_in_range(new_ring_position, 1, 26)) { ring_position = new_ring_position; }
}

void Rotor::set_position(int new_pos){
    position = new_pos;
}

void Rotor::set_mappings(const int new_mapping[CONVERSION_MAP_ARRAY_SIZE]){
    for(int i {min_position}; i <= max_position; i++) {
        forward_mapping[i] = new_mapping[i];
        reverse_mapping[ forward_mapping[i] ] = i;
    }
}

// forward is true if the current is coming from the keys, false if coming from the reflector
int Rotor::next(int normalized_input, bool forward, bool should_rotate){
    // the rotors should turn before the signal passes
    if(should_rotate) {
        // turn the next rotors if needed
        if(position == ring_position){
            turnover_flag = true;
        }

        if(position == max_position){
            position = min_position;
        }else{
            position++;
        }
    }

    int relative_input = position + normalized_input - 1;
    if(relative_input % max_position != 0){
        relative_input %= max_position;
    }else{
        relative_input = max_position;
    }

    int output_relative_to_current_pos;
    if(forward){
        output_relative_to_current_pos = forward_mapping[relative_input];
    }else{ // when coming back from reflector
        output_relative_to_current_pos = reverse_mapping[relative_input];
    }
    // calculate_f the normalized output value (ie. the number of steps from the 'start' position that the letter output at
    if(EMOps::is_in_range(max_position - position + output_relative_to_current_pos + 1, min_position, max_position)){
        return max_position - position + output_relative_to_current_pos + 1;
    }else{
        return output_relative_to_current_pos - position + 1;
    }
}

[[nodiscard]] bool Rotor::should_next_turn() const{
    return turnover_flag;
}

void Rotor::reset_turnover_flag(){
    turnover_flag = false;
}

[[nodiscard]] bool Rotor::pop_turnover_flag() {
    bool should_turnover {turnover_flag};
    turnover_flag = false;
    return should_turnover;
}

void Rotor::print_rotor_mappings() const{
    std::cout << "rotor_mappings:" << std::endl;
    for(int i = 1; i <= max_position; i++) {
        std::cout << "   " << i << " -> ";
        try {
            std::cout << forward_mapping[i] << std::endl;
        }catch(std::exception& e){
            std::cout << "no such value" << std::endl;
        }
    }
    std::cout << " ]" << std::endl;
}