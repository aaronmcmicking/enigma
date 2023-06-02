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
     */

    // the rotors should turn before the signal passes
    if(should_rotate) {
        // turn the next rotors if needed
        if(position == turnover_position){
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
        output_relative_to_current_pos = mappings.at(relative_input);
    }else{ // when coming back from reflector
        int i {min_position};
        while(i <= max_position){
            if(mappings.at(i) == relative_input){
                output_relative_to_current_pos = i;
                break;
            }
            i++;
        }
        if(i > max_position){ // searched through all rotor positions without finding a match (should not be possible)
            throw std::exception {};
        }
    }

//    std::cout << "pos = " << position << ", norm = " << output_relative_to_current_pos << std::endl;
    // calculate the normalized output value (ie. the number of steps from the 'start' position that the letter output at
    if(is_in_range(max_position - position + output_relative_to_current_pos + 1, min_position, max_position)){
//        std::cout << "in 1" << std::endl;
//        std::cout <<  "1) " << max_position - position + output_relative_to_current_pos << std::endl;
//        std::cout << "2) " << output_relative_to_current_pos - position << std::endl;
        return max_position - position + output_relative_to_current_pos + 1;
    }else{
//        std::cout << "in 2" << std::endl;
//        std::cout <<  "1) " << max_position - position + output_relative_to_current_pos << std::endl;
//        std::cout << "2) " << output_relative_to_current_pos - position << std::endl;
        return output_relative_to_current_pos - position + 1;
    }
}

bool Rotor::is_in_range(int num, int min, int max){
    return (num >= min) && (num <= max);
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