//
// Created by aaron on 2023-06-03.
//

#include <iostream>
#include "Headers/Plugboard.h"
#include "Headers/stdeo.h"
#include "Headers/Rotor.h"
#include <chrono>

Plugboard::Plugboard(): pairs {new int[CONVERSION_MAP_ARRAY_SIZE]} {;
    for(int i {0}; i <= Rotor::max_position; i++){
        pairs[i] = i;
    }
}

Plugboard::Plugboard(const std::string& pairs_str): pairs {new int[CONVERSION_MAP_ARRAY_SIZE]} {
    // parse string:
    for(int z {0}; z < CONVERSION_MAP_ARRAY_SIZE; z++) pairs[z] = 0;

    set_pairs(pairs_str);
}

[[nodiscard]] bool Plugboard::validate_plugboard_string(const std::string& str){
    const uint32_t MAX_PLUGBOARD_STRING_LENGTH {20};

    if(str.length() > MAX_PLUGBOARD_STRING_LENGTH){
        std::cout << str.length() << " exceeds max plugboard string length of "<< MAX_PLUGBOARD_STRING_LENGTH << " (were there more than 10 pairs included?)" << std::endl;
        throw std::exception {};
    }else if(str.length() % 2 != 0){
        std::cout << str.length() << " has non-even length "<< str.length() << " (is there a malformed pair included?)" << std::endl;
        throw std::exception {};
    }

    // checking character validity
    int count;
    for(char c {'a'}; c <= 'z'; c++){
        count = 0;
        for(uint32_t i {0}; i < str.length(); i++){
            if(str.at(i) == c) {
                count++;
            }
        }
        if(!(count == 0 || count == 1)){
            std::cout << "Invalid plugboard setting for '" << c << "' in: " << std::endl << "   {" << str << "}" << std::endl;

            return false;
        }
    } // for all chars in alphabet

    return true;
}

void Plugboard::set_pairs(const std::string &new_pairs) {
    std::string str_copy {};

    // send all chars to lowercase
    for(uint32_t i {}; i < new_pairs.length(); i++){
        if(isalpha(new_pairs.at(i))) {
            str_copy += static_cast<char>(tolower(new_pairs.at(i)));
        }
    }

    // validate string
    if(!validate_plugboard_string(str_copy)){
        throw std::exception {};
    }

    // parse and set
    parse_and_set_pairs(str_copy);
}

void Plugboard::parse_and_set_pairs(std::string &str) {
    // clear current pairs
    for(int w {}; w < CONVERSION_MAP_ARRAY_SIZE; w++){
        pairs[w] = w;
    }

    uint32_t i {};
    while(i < str.length()){
        int index;
        index = stdeo::ctoi(str.at(i++));
        int val {stdeo::ctoi(str.at(i++))};
        pairs[index] = val;
        pairs[val] = index;
    }
}

// `i` must already have correct indexing format (`i` is ith character in alphabet)
int Plugboard::convert_int(int i) {
    if(i >= CONVERSION_MAP_ARRAY_SIZE){
        std::cout << "Plugboard cannot convert invalid value (" << i << ")";
        throw std::exception {};
    }
    return pairs[i];
}

int Plugboard::convert_char(char c){
    return pairs[c - 'a' + 1];
}

void Plugboard::print(bool show_default_connections) {
    int* copy = without_dupes(); // format
    // print
    for(int index {0}; index < 27; index++) {
        if(copy[index] && (show_default_connections || copy[index] != index)) {
            std::cout << stdeo::itoc(index) << " <-> " << stdeo::itoc(copy[index]) << std::endl;
        }
    }
}

[[nodiscard]] int Plugboard::num_pairs() {
    int count {};
    for(int index {0}; index < 27; index++) {
        if(pairs[index] && pairs[index] != index) count++;
    }
    return count/2; // each pair has 2 elements
}

// assumes it is a valid plugboard string
int Plugboard::num_pairs(const std::string &pair_str) {
    int count {};
    for(char c: pair_str){
        if(isalpha(c)) {
            count++;
        }
    }
    return count / 2; // each pair has 2 elements
}

int* Plugboard::without_dupes(){
    // copy
    static int copy[CONVERSION_MAP_ARRAY_SIZE] {};
    for(int w {}; w < CONVERSION_MAP_ARRAY_SIZE; w++) {
        copy[w] = pairs[w];
    }
    // remove dupes
    for(int w {}; w < CONVERSION_MAP_ARRAY_SIZE; w++){
        if(copy[w] != w){
            copy[copy[w]] = 0;
        }
    }
    return copy;
}

std::string Plugboard::get_pairs() {
    std::string str {};
    int* copy = without_dupes();
    for(int i {}; i < CONVERSION_MAP_ARRAY_SIZE; i++){
        if(copy[i]){
            str += static_cast<char>(toupper(stdeo::itoc(i)));
            str += static_cast<char>(toupper(stdeo::itoc(copy[i])));
            str += ' ';
        }
    }
    str.pop_back(); // removes hanging space at end of string
    return str;
}

bool Plugboard::can_add(const std::string& new_pair, const int* pairs) {
    bool first {pairs[stdeo::ctoi(new_pair[0])] == stdeo::ctoi(new_pair[0]) };
    bool second {pairs[stdeo::ctoi(new_pair[1])] == stdeo::ctoi(new_pair[1]) };
    return first && second;
}

bool Plugboard::can_add(const std::string &new_pair, const std::string &pairs) {
    for(char c: pairs){
        if(isspace(c)) continue;
        int c_lower {tolower(c)};
        if(c_lower == tolower(new_pair[0]) || c_lower == tolower(new_pair[1])){
            return false;
        }
    }
    if(num_pairs(pairs) >= 10) return false;
    return true;
}

bool Plugboard::can_add(const std::string &new_pair){
    // omits calls to stdeo::coti() for speed since this function is called extremely often during some decryption attacks
    bool first {pairs[ (tolower(new_pair[0]) - 'a' + 1) ] == (tolower(new_pair[0]) - 'a' + 1 )};
    bool second {pairs[ (tolower(new_pair[1]) - 'a' + 1) ] == (tolower(new_pair[1]) - 'a' + 1 )};
    return first && second;
}