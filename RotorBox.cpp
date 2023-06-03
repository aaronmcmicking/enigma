//
// Created by aaron on 2023-06-01.
//

#include <iostream>
#include "RotorBox.h"
#include "RotorMappingBuilder.h"

RotorBox::RotorBox(): reflector {Reflector()} {
    RotorMappingBuilder::set_init(false);
    RotorMappingBuilder::nullify_mappings();
    std::map<int, int> mapI = RotorMappingBuilder::get_rotor_mapping(1);
    std::map<int, int> mapII = RotorMappingBuilder::get_rotor_mapping(2);
    std::map<int, int> mapIII = RotorMappingBuilder::get_rotor_mapping(3);
    std::map<int, int> mapIV = RotorMappingBuilder::get_rotor_mapping(4);
    std::map<int, int> mapV = RotorMappingBuilder::get_rotor_mapping(5);
    std::map<int, int> mapVI = RotorMappingBuilder::get_rotor_mapping(6);
    std::map<int, int> mapVII = RotorMappingBuilder::get_rotor_mapping(7);
    std::map<int, int> mapVIII = RotorMappingBuilder::get_rotor_mapping(8);

    RotorI.set_mappings(mapI);
    RotorI.set_turnover_position(Operations::ctoi('r'));

    RotorII.set_mappings(mapII);
    RotorI.set_turnover_position(Operations::ctoi('f'));

    RotorIII.set_mappings(mapIII);
    RotorIII.set_turnover_position(Operations::ctoi('w'));

    RotorIV.set_mappings(mapIV);
    RotorIV.set_turnover_position(Operations::ctoi('k'));

    RotorV.set_mappings(mapV);
    RotorV.set_turnover_position(Operations::ctoi('a'));

    // these rotors should have 2 turnovers each (at 'a' and 'n'), but this is not currently supported
    RotorVI.set_mappings(mapVI);
    RotorVII.set_mappings(mapVII);
    RotorVIII.set_mappings(mapVIII);
    RotorVI.set_turnover_position(Operations::ctoi('a'));
    RotorVII.set_turnover_position(Operations::ctoi('a'));
    RotorVIII.set_turnover_position(Operations::ctoi('a'));

    rotors_in_place = new Rotor[]{RotorI, RotorII, RotorIII};
}

Rotor RotorBox::get_rotor(int rotor_number){
    Rotor rotors[] {RotorI, RotorII, RotorIII, RotorIV, RotorV, RotorVI,RotorVII, RotorVIII};
    return rotors[rotor_number-1];
}

Rotor* RotorBox::get_all_rotors(){
    return new Rotor[] {RotorI, RotorII, RotorIII, RotorIV, RotorV, RotorVI, RotorVII, RotorVIII};
}

void RotorBox::set_placed_rotor(int rotor_number, int position){
    if(rotors_in_place == nullptr) throw std::exception {};
    rotors_in_place[position-1] = get_rotor(rotor_number);
}

Rotor* RotorBox::get_rotors_in_place() {
    if(rotors_in_place == nullptr) throw std::exception {};
    return new Rotor[] {rotors_in_place[0], rotors_in_place[1], rotors_in_place[2]};
}

// rotor_pos = 1st, 2nd, or 3rd rotor, and 1 <= pos <= 26
Rotor* RotorBox::set_rotor_pos(int rotor_pos, int pos) {
    if(rotor_pos < 1 || rotor_pos > 3 || pos < 1 || pos > 26){ // bounds checking
        throw std::exception {};
    }
    rotors_in_place[rotor_pos].set_position(pos);
    return rotors_in_place;
}

Rotor* RotorBox::set_rotor_pos(int pos[3]){
    for(int i = 0; i < 3; i++){
        if(pos[i] < 1 || pos[i] > 26){ // bounds checking
            throw std::exception {};
        }
        rotors_in_place[i].set_position(pos[i]);
    }
}

char RotorBox::convert_char(char c) {
    bool rotate {true};
    int next_input;

    if(rotors_in_place == nullptr){
        std::cout << "rotor array is null" << std::endl;
        return -1;
    }

    // iterate through rotors moving towards the reflector
    next_input = Operations::ctoi(c);
    for(int i {0}; i < 3; i++){
        next_input = rotors_in_place[i].next(next_input, true, rotate);
        rotate = rotors_in_place[i].next_should_turn();
        rotors_in_place[i].reset_turnover_flag();
    }

    // reflect
    next_input = reflect(next_input);

    // iterate through the rotors coming back from the reflector
    for(int i {2}; i >= 0; i--){
        next_input = rotors_in_place[i].next(next_input, false, false);
    }

    return Operations::itoc(next_input);
}

int RotorBox::reflect(int input){
    return reflector.reflect(input);
}

void RotorBox::set_reflector(char c){
    reflector.set_reflector(c);
}

Reflector RotorBox::get_reflector(){
    return reflector;
}