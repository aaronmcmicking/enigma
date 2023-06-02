#include <iostream>
#include "RotorBox.h"
#include <fstream>
#include <cctype>

#define MAX_INPUT_STRING_LENGTH 10000

std::string strip_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

bool check_char_duping(std::string s1, std::string s2){
    int i {};
    unsigned long long const s1_l {s1.length()};
    unsigned long long const s2_l {s2.length()};

    while(i < s1_l && i < s2_l){
        if(s1.at(i) == s2.at(i)){
            return false;
        }
        i++;
    }
    return true;
}

void in_con_out(const std::string& in_f, const std::string& out_f, RotorBox rb){
    std::ifstream in_file {};
    in_file.open(in_f);
    char in_buf[MAX_INPUT_STRING_LENGTH] {};
    in_file.read(in_buf, MAX_INPUT_STRING_LENGTH-1);
    in_file.close();
    std::string in_str = strip_text(in_buf);

    std::string buffer {};
    for(char c: in_str){
        char c1 = rb.convert_char(c);
//        std::cout << static_cast<char>(toupper(c1));
        buffer += c1;
    }

    std::cout << std::endl;

    std::ofstream out_file {};
    out_file.open(out_f);
    out_file << buffer;
    out_file.close();
}

int main(){
    RotorBox rotor_box {};

    std::cout << "Testing rotors" << std::endl;

    int pos[] {8, 23, 9};
    rotor_box.set_rotor_pos(pos);

    in_con_out("input.txt", "output_1.txt", rotor_box);

    rotor_box.set_rotor_pos(pos);
    Rotor* rs {rotor_box.get_rotors_in_place()};
    std::cout << "rotors: {" << rs[0].get_position() << ", " << rs[1].get_position() << ", " << rs[2].get_position() << "}" << std::endl;

    in_con_out("output_1.txt", "output_2.txt", rotor_box);

//    std::string str {"It might be urged that when playing the ‘imitation game’ the best strategy for the machine may possibly be something other than imitation of the behaviour of a man. This may be, but I think it is unlikely that there is any great effect of this kind. In any case there is no intention to investigate here the theory of the game, and it will be assumed that the best strategy is to try to provide answers that would naturally be given by a man."};
//    std::string str1 {};
//    str = strip_text(str);

//    std::cout << (check_char_duping(str, str1) ? "true" : "false") << std::endl;


//    std::cout << "rotors: {" << rs[0].get_position() << ", " << rs[1].get_position() << ", " << rs[2].get_position() << "}" << std::endl;
//    std::cout << "rotation points: {" << rs[0].get_turnover_position() << ", " << rs[1].get_turnover_position() << ", " << rs[2].get_turnover_position() << "}" << std::endl;





    std::cout << "Done" << std::endl;

    // rotor_box.set_rotor_pos(position, num of rotor)

    return 0;
}
