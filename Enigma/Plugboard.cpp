//
// Created by aaron on 2023-06-03.
//

#include <iostream>
#include "Headers/Plugboard.h"
#include "Headers/EMOps.h"
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
//    std::cout << "plugboard validation received {" << str << "}" << " with length " << str.length() << std::endl;


    const uint MAX_PLUGBOARD_STRING_LENGTH {20};

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
        for(uint i {0}; i < str.length(); i++){
            if(str.at(i) == c) {
                count++;
            }
//            else if(!isalpha(str.at(i)) && !isspace(str.at(i)) ){
//                std::cout << "Invalid plugboard character '" << str.at(i) << "' in: " << std::endl << "   {" << str << "}" << std::endl;
//            }
        } // for all chars in string
        if(!(count == 0 || count == 1)){
            std::cout << "Invalid plugboard setting for '" << c << "' in: " << std::endl << "   {" << str << "}" << std::endl;

            return false;
        }
    } // for all chars in alphabet

    return true;
}

void Plugboard::set_pairs(const std::string &new_pairs) {
    std::string str_copy {};

//    std::cout << "new_pairs.len = " << new_pairs.length() << std::endl;
    uint i;
    // send all chars to lowercase
    for (i = 0; i < new_pairs.length(); i++){
        if(isalpha(new_pairs.at(i))) {
            str_copy += static_cast<char>(tolower(new_pairs.at(i)));
        }
    }

//    if(new_pairs.length() > 0) std::cout << "1.2.1" << std::endl;
    // validate string
    if(!validate_plugboard_string(str_copy)){
        throw std::exception {};
    }
//    if(new_pairs.length() > 0) std::cout << "1.2.2" << std::endl;

    // parse and set
    parse_and_set_pairs(str_copy);
//    if(new_pairs.length() > 0) std::cout << "1.2.3" << std::endl;
}

void Plugboard::parse_and_set_pairs(std::string &str) {
    // clear current pairs
    for(int w {}; w < CONVERSION_MAP_ARRAY_SIZE; w++){
        pairs[w] = w;
    }

//    if(str.length() > 0)
//        std::cout << "parse_and_set_pairs: str = {" << str << "} with length = " << str.length() << std::endl;

    uint i {};
    while(i < str.length()){
        int index;
        index = EMOps::ctoi(str.at(i++));
//        i++;
        int val {EMOps::ctoi(str.at(i++))};
        pairs[index] = val;
        pairs[val] = index;
//        i += 2;
    }
}

// i must already have correct indexing format
int Plugboard::convert_int(int i) {
    if(i >= CONVERSION_MAP_ARRAY_SIZE){
        std::cout << "Plugboard cannot convert invalid value (" << i << ")";
        throw std::exception {};
    }
    return pairs[i];
}

// wrapper for convert_int(int c)
int Plugboard::convert_char(char c){
    return pairs[c - 'a' + 1];
}

void Plugboard::print() {
    int* copy = without_dupes();
    // print
    for(int index {0}; index < 27; index++) {
        if(copy[index]) {
            std::cout << EMOps::itoc(index) << " <-> " << EMOps::itoc(copy[index]) << std::endl;
        }
    }
}

[[nodiscard]] int Plugboard::num_pairs() {
    int count {};
    for(int index {0}; index < 27; index++) {
        if(pairs[index] && pairs[index] != index) count++;
    }
    return count/2;
}

// assumes it is a valid plugboard string
int Plugboard::num_pairs(const std::string &pair_str) {
    int count {};
    for(char c: pair_str){
        if(isalpha(c)) {
            count++;
        }
    }
    return count / 2;
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
            str += static_cast<char>(toupper(EMOps::itoc(i)));
            str += static_cast<char>(toupper(EMOps::itoc(copy[i])));
            str += ' ';
        }
    }
    str.pop_back(); // removes unwanted space at end of string
    return str;
}

bool Plugboard::can_add(const std::string& new_pair, const int* pairs) {
    return pairs[EMOps::ctoi(new_pair[0])] == EMOps::ctoi(new_pair[0]);
}

bool Plugboard::can_add(const std::string &new_pair, const std::string &pairs) {
    if(num_pairs(pairs) >= 10) return false;
    for(char c: pairs){
        if(isspace(c)) continue;
        int c_lower {tolower(c)};
        if(c_lower == tolower(new_pair[0]) || c_lower == tolower(new_pair[1])){
            return false;
        }
    }
    return true;
}