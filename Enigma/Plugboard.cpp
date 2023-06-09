//
// Created by aaron on 2023-06-03.
//

#include <iostream>
#include "Headers/Plugboard.h"
#include "Headers/EMOps.h"
#include "Headers/Rotor.h"


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
    // checking number of pairs
    // each pair has 3 characters in str EXCEPT the final pair, which has two
    // there can be no more than ten pairs
    // so str.length() <= 9*3 + 1*2 = 29
    if(str.length() > 29){
        std::cout << str.length() << " exceeds max plugboard string length of 28 (were there more than 10 pairs included?)" << std::endl;
        throw std::exception {};
    }

    // checking character validity
    int count {};
    for(char c {'a'}; c <= 'z'; c++){
        count = 0;
        for(uint i {0}; i < str.length(); i++){
            if(str.at(i) == c) {
                count++;
            }else if(!isalpha(str.at(i)) && !isspace(str.at(i)) ){
                std::cout << "Invalid plugboard character '" << str.at(i) << "' in: " << std::endl << "   {" << str << "}" << std::endl;
            }
        } // for all chars in string
        if(!(count == 0 || count == 1)){
            std::cout << "Invalid plugboard setting for '" << c << "' in: " << std::endl << "   {" << str << "}" << std::endl;

            return false;
        }
    } // for all chars in alphabet

    // checking format
    uint w {};
    while(w < str.length()){
        char a, b, c;
        a = str.at(w++);
        b = str.at(w++);
        if(!isalpha(a) || !isalpha(b)){
            std::cout << "Invalid plugboard setting segment in: " << std::endl << "   {" << str << "}" << std::endl;
            throw std::exception {};
        }else if(w < str.length()-1){
            // seperated space checking since the last pair does not have a following space
            c = str.at(w++);
            if(!isspace(c)){
                std::cout << "Invalid plugboard setting segment in: " << std::endl << "   {" << str << "}" << std::endl;
            } // if !isspace(c)
        } // if ( !isalpha(a) || !isalpha(b) ) else ( w < str.len-1)
    } // while (w < str.len)
    return true;
}

void Plugboard::set_pairs(const std::string &new_pairs) {
    std::string str_copy = new_pairs;

    // send all chars to lowercase
    for (uint i {0}; i < str_copy.length(); i++){
        str_copy.at(i) = static_cast<char>(tolower(str_copy.at(i)));
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

    uint i {};
    while(i < str.length()){
        int index;
        index = EMOps::ctoi(str.at(i));
        i++;
        int val {EMOps::ctoi(str.at(i))};
        pairs[index] = val;
        pairs[val] = index;
        i += 2;
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
    int i{ EMOps::ctoi(static_cast<char>(tolower(c))) };
    if(i >= CONVERSION_MAP_ARRAY_SIZE){
        std::cout << "Plugboard cannot convert invalid value (" << i << ")";
        throw std::exception {};
    }
    return pairs[i];
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