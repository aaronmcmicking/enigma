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

int Rotor::next(bool forward, int input_position){
    /*
     * Assume input position is normalized
     *
     * to find correct key, get diff between current position and normalized input position
     *
     * offset = current position
     *
     *
     */
    position++; // the rotors should turn before the signal is passes

    // turn the next rotors if needed
    if(position-1 == turnover_position){
        turnover_flag = true;
    }

    int offset = position;
    int effective_input = offset + input_position;
    if(effective_input != 26){
        effective_input %= 26;
    }
    int to_return;
    if(forward) {
        to_return = mappings.at(effective_input);
    }else{ // when coming back from reflector
        int i {1};
        while(i <= 26){
            if(mappings.at(i) == effective_input){
                to_return = i;
                break;
            }
            i++;
        }
        if(i > 26){
            throw std::exception {};
        }
    }

    return to_return;
}

[[nodiscard]] bool Rotor::next_should_turn() const{
    return turnover_flag;
}

void Rotor::reset_turnover_flag(){
    turnover_flag = false;
}

void Rotor::print_rotor_mappings() const{
    std::cout << "mappings:" << std::endl;
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