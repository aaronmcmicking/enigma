//
// Created by aaron on 2023-06-05.
//

#include "EnigmaMachine.h"
#include <string>
#include <iostream>
#include <fstream>

EnigmaMachine::EnigmaMachine(): rotor_box {}, plugboard {} {}

EnigmaMachine::EnigmaMachine(int rotors[3], int* rotor_pos, char reflector, const std::string& plugboard_settings) {
    rotor_box = RotorBox();
    plugboard = Plugboard(plugboard_settings);
    rotor_box.set_placed_rotor(rotors, rotor_pos);
    rotor_box.set_reflector(reflector);
}

EnigmaMachine::EnigmaMachine(EnigmaConfig config) {
    rotor_box = RotorBox();
    plugboard = Plugboard(config.plugboard);
    rotor_box.set_placed_rotor(config.rotors, config.rotor_pos);
    rotor_box.set_reflector(config.reflector);
}

bool EnigmaMachine::encrypt_or_decrypt_file(const std::string& in_file_name, const std::string& out_file_name){
    char in_buf[MAX_INPUT_STRING_LENGTH] {};
    std::ifstream in_file {};
    in_file.open(in_file_name);
    in_file.read(in_buf, MAX_INPUT_STRING_LENGTH-1);
    in_file.close();
    std::string in_str = EMOps::strip_text(in_buf);

    std::string buffer {};
    for(char c: in_str){
//        std::cout << static_cast<char>(toupper(c1));
        buffer += EMOps::itoc(convert_char(c));
    }

//    std::cout << std::endl;

    std::ofstream out_file {};
    out_file.open(out_file_name);
    out_file << buffer;
    out_file.close();
    return true;
}

std::string EnigmaMachine::encrypt_or_decrypt(const std::string& in){
    std::string out {};
    for(char c: in){
        out += EMOps::itoc(convert_char(c));
    }
    return out;
}

int EnigmaMachine::convert_char(char c) {
    int c1 = plugboard.convert_char(c);
    c1 = rotor_box.convert_int(c1);
    if(c1 == -1){
        throw std::exception {};
    }
    c1 = plugboard.convert_int(c1);
    return c1;
}

void EnigmaMachine::set_rotors(const int *rotors) {
    rotor_box.set_placed_rotor(rotors);
}

void EnigmaMachine::set_rotor_pos(const int *pos) {
    rotor_box.set_rotor_pos(pos);
}

void EnigmaMachine::set_reflector(char c) {
    rotor_box.set_reflector(c);
}

void EnigmaMachine::set_plugboard_settings(const std::string& settings) {
    plugboard.set_pairs(settings);
}

void EnigmaMachine::set_config(const EnigmaConfig& config){
    set_rotors(config.rotors);
    set_rotor_pos(config.rotor_pos);
    set_reflector(config.reflector);
    set_plugboard_settings(config.plugboard);
}