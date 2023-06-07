//
// Created by aaron on 2023-06-01.
//

#include <iostream>
#include "Headers/RotorBox.h"
#include "Headers/RotorMappingBuilder.h"

RotorBox::RotorBox(): reflector {Reflector()} {
    RotorMappingBuilder::set_init(false);
    RotorMappingBuilder::nullify_mappings();

    // all below have size Rotor::CONVERSION_MAP_ARRAY_SIZE and are 1-indexed
    int* mapI = RotorMappingBuilder::get_rotor_mapping(1);
    int* mapII = RotorMappingBuilder::get_rotor_mapping(2);
    int* mapIII = RotorMappingBuilder::get_rotor_mapping(3);
    int* mapIV = RotorMappingBuilder::get_rotor_mapping(4);
    int* mapV = RotorMappingBuilder::get_rotor_mapping(5);
    int* mapVI = RotorMappingBuilder::get_rotor_mapping(6);
    int* mapVII = RotorMappingBuilder::get_rotor_mapping(7);
    int* mapVIII = RotorMappingBuilder::get_rotor_mapping(8);

    RotorI.set_mappings(mapI);
    RotorI.set_turnover_position(EMOps::ctoi('r'));

    RotorII.set_mappings(mapII);
    RotorI.set_turnover_position(EMOps::ctoi('f'));

    RotorIII.set_mappings(mapIII);
    RotorIII.set_turnover_position(EMOps::ctoi('w'));

    RotorIV.set_mappings(mapIV);
    RotorIV.set_turnover_position(EMOps::ctoi('k'));

    RotorV.set_mappings(mapV);
    RotorV.set_turnover_position(EMOps::ctoi('a'));

    // these rotors should have 2 turnovers each (at 'a' and 'n'), but this is not currently supported
    RotorVI.set_mappings(mapVI);
    RotorVII.set_mappings(mapVII);
    RotorVIII.set_mappings(mapVIII);
    RotorVI.set_turnover_position(EMOps::ctoi('a'));
    RotorVII.set_turnover_position(EMOps::ctoi('a'));
    RotorVIII.set_turnover_position(EMOps::ctoi('a'));

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

void RotorBox::set_placed_rotor(const int *rotors) {
    if(rotors_in_place == nullptr) throw std::exception {};
    for(int i {}; i < 3; i++){
        rotors_in_place[i] = get_rotor(rotors[i]);
    }
}

void RotorBox::set_placed_rotor(int *rotors, int* pos) {
    set_placed_rotor(rotors);
    for(int i {}; i < 3; i++){
        rotors_in_place[i].set_position(pos[i]);
    }
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

Rotor* RotorBox::set_rotor_pos(const int pos[3]){
    for(int i = 0; i < 3; i++){
        if(pos[i] < 1 || pos[i] > 26){ // bounds checking
            throw std::exception {};
        }
        rotors_in_place[i].set_position(pos[i]);
    }
    return rotors_in_place;
}

int RotorBox::convert_int(int i) {
    bool rotate {true};
    int next_input;

    if(rotors_in_place == nullptr){
        std::cout << "rotor array is null" << std::endl;
        return -1;
    }

    // iterate through rotors moving towards the reflector
    next_input = i;
    for(int w {0}; w < 3; w++){
        next_input = rotors_in_place[w].next(next_input, true, rotate);
        rotate = rotors_in_place[w].next_should_turn();
        rotors_in_place[w].reset_turnover_flag();
    }

    // reflect
    next_input = reflect(next_input);

    // iterate through the rotors coming back from the reflector
    for(int w {2}; w >= 0; w--){
        next_input = rotors_in_place[w].next(next_input, false, false);
    }

    return next_input;
}

int RotorBox::reflect(int input){
    return reflector.reflect(input);
}

void RotorBox::set_reflector(char c){
    reflector.set_reflector(c);
}

void RotorBox::set_reflector(Reflector r) {
    reflector.set_reflector(r);
}

Reflector RotorBox::get_reflector(){
    return reflector;
}