//
// Created by aaron on 2023-06-05.
//

#include "Headers/EnigmaMachine.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

EnigmaMachine::EnigmaMachine(): rotor_box {}, plugboard {} {}

EnigmaMachine::EnigmaMachine(int rotors[3], int* rotor_pos, int* ring_pos, char reflector, const std::string& plugboard_settings) {
    rotor_box = RotorBox();
    plugboard = Plugboard(plugboard_settings);
    rotor_box.set_rotors(rotors, rotor_pos);
    rotor_box.set_rotor_ring_pos(ring_pos);
    rotor_box.set_reflector(reflector);
}

EnigmaMachine::EnigmaMachine(const EnigmaConfig& config) {
    rotor_box = RotorBox();
    plugboard = Plugboard(config.plugboard);
    rotor_box.set_rotors(config.rotors, config.rotor_pos);
    rotor_box.set_reflector(config.reflector);
    rotor_box.set_rotor_ring_pos(config.ring_pos);
}

void EnigmaMachine::encrypt_or_decrypt_file(const std::string& in_file_path, const std::string& out_file_path){
    // read input
    char in_buf[MAX_INPUT_STRING_LENGTH] {};
    std::ifstream in_file {in_file_path};
    in_file.get(in_buf, MAX_INPUT_STRING_LENGTH);
    in_file.close();
    std::string in_str = EMOps::strip_text(in_buf);

    // convert
    std::string buffer {};
    for(char c: in_str){
//        std::cout << static_cast<char>(toupper(c1));
        buffer += EMOps::itoc(convert_char(c));
    }

    // write output
    std::ofstream out_file {};
    out_file.open(out_file_path);
    out_file << buffer;
    out_file.close();
}

std::string EnigmaMachine::encrypt_or_decrypt_str(const std::string& in){
    std::string out {};
    for(char c: in){
        out += EMOps::itoc(convert_char(c));
    }
    return out;
}

void EnigmaMachine::encrypt_or_decrypt_arr(char *dest, const char *src, int size) {
    int i {};
    while(i < size && src[i] != '\0'){
        dest[i] = EMOps::itoc(convert_char(src[i]));
        i++;
    }
}

//void EnigmaMachine::encrypt_or_decrypt_arr_direct(char *dest, const char* src, int size) {
//    int i {}, c1;
//    while(i < size && src[i] != '\0'){
//        c1 = plugboard.convert_char(src[i]);
//        c1 = rotor_box.convert_int(c1);
//        dest[i++] = static_cast<char>(plugboard.convert_int(c1) + 'a' - 1);
//    }
//}

void EnigmaMachine::encrypt_or_decrypt_arr_direct(char *dest, const char* src, int size) {
    int i {}, c1;
    while(i < size){
        c1 = plugboard.convert_char(*(src++));
        c1 = rotor_box.convert_int(c1);
        dest[i++] = static_cast<char>(plugboard.convert_int(c1) + 'a' - 1);
    }
}

void EnigmaMachine::encrypt_or_decrypt_arr_direct(char *dest, const char* src) {
    int c1;
    while(*src != '\0'){
        c1 = plugboard.convert_char(*(src++));
        c1 = rotor_box.convert_int(c1);
        *(dest++) = static_cast<char>(plugboard.convert_int(c1) + 'a' - 1);
    }
}

int EnigmaMachine::convert_char(char c) {
    int c1 = plugboard.convert_char(c);
    c1 = rotor_box.convert_int(c1);
    if(c1 == -1){ // -1 is signal value that RotorBox::convert_int(int) may return
        throw std::exception {};
    }
    c1 = plugboard.convert_int(c1);
    return c1;
}

void EnigmaMachine::set_rotors(const int *rotors) {
    rotor_box.set_rotors(rotors);
}

void EnigmaMachine::set_rotor_pos(const int *pos) {
    rotor_box.set_rotor_pos(pos);
}

void EnigmaMachine::set_ring_pos(const int *ring_pos) {
    rotor_box.set_rotor_ring_pos(ring_pos);
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
    set_ring_pos(config.ring_pos);
    set_reflector(config.reflector);
    set_plugboard_settings(config.plugboard);
}

void EnigmaMachine::print_config_object(const EnigmaConfig& config){
    std::cout << "rotors = ";
    for(int i{}; i < 3; i++) {
        std::cout << config.rotors[i] << " ";
    }
    std::cout << std::endl << "pos = ";
    for(int i{}; i < 3; i++) {
        std::cout << config.rotor_pos[i] << " ";
    }
    std::cout << std::endl << "ref = " << config.reflector << std::endl;
    std::cout << "plugboard = " << config.plugboard << std::endl;
}

[[maybe_unused]] void EnigmaMachine::print_config(){
    (void) rotor_box; // removes "can be made static" msg
    std::cout << "EnigmaMachine::print_config: IMPLEMENT ME" << std::endl;
}

void EnigmaMachine::copy_config(EnigmaConfig &dest, EnigmaConfig &src) {
    EMOps::rep_arr3(dest.rotors, src.rotors);
    EMOps::rep_arr3(dest.rotor_pos, src.rotor_pos);
    EMOps::rep_arr3(dest.ring_pos, src.ring_pos);
    dest.reflector = src.reflector;
    dest.plugboard = src.plugboard;
}

Plugboard& EnigmaMachine::get_plugboard(){
    return plugboard;
}