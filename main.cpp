#include <iostream>
#include "RotorBox.h"
#include <fstream>
#include <cctype>
#include <ctime>

#define MAX_INPUT_STRING_LENGTH 10000

// return true if no dups found, false otherwise (true is desired generally)
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

bool fcheck_char_duping(const std::string& file1_n, const std::string& file2_n){
    char buf1[MAX_INPUT_STRING_LENGTH] {};
    char buf2[MAX_INPUT_STRING_LENGTH] {};

    std::ifstream file1 {file1_n};
    file1.read(buf1, MAX_INPUT_STRING_LENGTH);

    std::ifstream file2 {file2_n};
    file2.read(buf2, MAX_INPUT_STRING_LENGTH);

    std::string sbuf1 {buf1};
    std::string sbuf2 {buf2};

    unsigned long long length = sbuf1.length() < sbuf2.length() ? sbuf1.length() : sbuf2.length(); // get min length
    int i {0};
    while(i < length){
        if(sbuf1.at(i) == sbuf2.at(i)){
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
    std::string in_str = Operations::strip_text(in_buf);

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


    std::cout << "starting" << std::endl;
//    for(unsigned long long i {0}; i < 1000*1000*10; i++){
//        rotor_box.convert_char('a');
//    }
//    std::cout << "finished" << std::endl;


    auto start = std::clock();

    int pos[] {8, 23, 9};
    rotor_box.set_rotor_pos(pos);
    in_con_out("input.txt", "output_1.txt", rotor_box);

    rotor_box.set_rotor_pos(pos);
    Rotor* rs {rotor_box.get_rotors_in_place()};
    std::cout << "rotors: {" << rs[0].get_position() << ", " << rs[1].get_position() << ", " << rs[2].get_position() << "}" << std::endl;

    in_con_out("output_1.txt", "output_2.txt", rotor_box);

    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;


//    std::cout << (fcheck_char_duping("input.txt", "output_1.txt") ? "passed" : "false") << " dupe check" << std::endl;

//    std::cout << "rotors: {" << rs[0].get_position() << ", " << rs[1].get_position() << ", " << rs[2].get_position() << "}" << std::endl;
//    std::cout << "rotation points: {" << rs[0].get_turnover_position() << ", " << rs[1].get_turnover_position() << ", " << rs[2].get_turnover_position() << "}" << std::endl;

    std::cout << "Done" << std::endl;

    // rotor_box.set_rotor_pos(position, num of rotor)

    return 0;
}
