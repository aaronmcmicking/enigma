//
// Created by aaron on 2023-06-01.
//

#include <iostream>
#include "Headers/Rotor.h"
#include "Headers/EMOps.h"

void Rotor::fill_default_mappings(){
    for(int i {min_position}; i <= max_position; i++){
        mappings[i] = i;
    }
}

Rotor::Rotor(): position {min_position}, ring_position {max_position}, mappings {} {
    fill_default_mappings();
}

Rotor::Rotor(int initial_position, int ring_pos): position {initial_position}, ring_position {ring_pos}, mappings {} {
    fill_default_mappings();
}

Rotor::Rotor(int initial_position, int ring_pos, const int map[CONVERSION_MAP_ARRAY_SIZE])
        : position {initial_position}, ring_position {ring_pos}, mappings {}
{
    for(int i {min_position}; i <= max_position; i++){
        mappings[i] = map[i];
    }
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

void Rotor::set_mappings(const int new_mappings[CONVERSION_MAP_ARRAY_SIZE]){
    for(int i {min_position}; i <= max_position; i++) {
        mappings[i] = new_mappings[i];
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
    if(forward) {
        output_relative_to_current_pos = mappings[relative_input];
    }else{ // when coming back from reflector
        int i {min_position};
        while(i <= max_position && mappings[i] != relative_input){
            if(i >= max_position){
                std::cout << "couldn't find mapping for value " << i << " from reflector" << std::endl;
                throw std::exception {};
            }
            i++;
        }
        output_relative_to_current_pos = i;
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
    bool b {turnover_flag};
    turnover_flag = false;
    return b;
}

void Rotor::print_rotor_mappings() const{
    std::cout << "rotor_mappings:" << std::endl;
    for(int i = 1; i <= max_position; i++) {
        std::cout << "   " << i << " -> ";
        try {
            std::cout << mappings[i] << std::endl;
        }catch(std::exception& e){
            std::cout << "no such value" << std::endl;
        }
    }
    std::cout << " ]" << std::endl;
}