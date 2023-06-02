//
// Created by aaron on 2023-06-01.
//

#include <iostream>
#include "Rotor.h"

void Rotor::fill_default_mappings(){
    for(int i = min_position; i <= max_position; i++){
        mappings.insert(std::pair<int, int>{i, i});
    }
}

Rotor::Rotor(): position {min_position}, turnover_position {max_position} {
    fill_default_mappings();
}

Rotor::Rotor(int initial_position, int turnover_pos): position {initial_position}, turnover_position {turnover_pos}{
    fill_default_mappings();
}

Rotor::Rotor(int initial_position, int turnover_pos, std::map<int, int>& map)
        : position {initial_position}, turnover_position {turnover_pos}, mappings {map}
{ }

[[nodiscard]] int Rotor::get_position() const{
    return position;
}

[[nodiscard]] int Rotor::get_turnover_position() const{
    return turnover_position;
}

void Rotor::set_turnover_position(int new_turnover_pos){
    turnover_position = new_turnover_pos;
}

void Rotor::set_position(int new_pos){
    position = new_pos;
}

void Rotor::set_mappings(std::map<int, int> const& new_mappings){
    mappings = new_mappings;
}

// forward is true if the current is coming from the keys, false if coming from the reflector
int Rotor::next(int normalized_input, bool forward, bool should_rotate){
    /*
     * Assume input position is normalized
     *
     * to find correct key, get diff between current position and normalized input position
     *
     * offset = current position
     *
     */

    // the rotors should turn before the signal passes
    if(should_rotate) {
        // turn the next rotors if needed
        if(position == turnover_position){
            turnover_flag = true;
        }
        if(position == 26){
            position = 1;
        }else{
            position++;
        }
    }

    int offset = position;
    int relative_input = offset + normalized_input;
    if(relative_input % 26 != 0){
        relative_input %= 26;
    }else{
        relative_input = 26;
    }
    int normalized_output;
    if(forward) {
        normalized_output = mappings.at(relative_input);
    }else{ // when coming back from reflector
        int i {1};
        while(i <= 26){
            if(mappings.at(i) == relative_input){
                normalized_output = i;
                break;
            }
            i++;
        }
        if(i > 26){ // searched through all rotor positions without finding a match (should not be possible)
            throw std::exception {};
        }
    }
    return normalized_output;
}

[[nodiscard]] bool Rotor::next_should_turn() const{
    return turnover_flag;
}

void Rotor::reset_turnover_flag(){
    turnover_flag = false;
}

void Rotor::print_rotor_mappings() const{
    std::cout << "rotor_mappings:" << std::endl;
    for(int i = 1; i <= max_position; i++) {
        std::cout << "   " << i << " -> ";
        try {
            std::cout << mappings.at(i) << std::endl;
        }catch(std::exception& e){
            std::cout << "no such value" << std::endl;
        }
    }
    std::cout << " ]" << std::endl;
}