#include <iostream>
#include "RotorBox.h"
#include <fstream>
#include <cctype>

std::string strip_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

int main(){
    RotorBox rotor_box {};
//    Rotor* r_arr {rotor_box.get_all_rotors()};
//    for(int i = 0; i < 8; i++){
//        r_arr[i].print_rotor_mappings();
//    }

    std::cout << "Testing rotors" << std::endl;

//    std::string str {"I propose to consider the question, ‘Can machines think?’ This should begin with definitions of the meaning of the terms ‘machine’ and ‘think’. The definitions might be framed so as to reflect so far as possible the normal use of the words, but this attitude is dangerous. If the meaning of the words ‘machine’ and ‘think’ are to be found by examining how they are commonly used it is difficult to escape the conclusion that the meaning and the answer to the question, ‘Can machines think?’ is to be sought in a statistical survey such as a Gallup poll. But this is absurd. Instead of attempting such a definition I shall replace the question by another, which is closely related to it and is expressed in relatively unambiguous words."};
    std::string str {"cooglppiuexipdkzqvdopftjqfazaedajiiyuwridfbyrkvdyzspikgesxgiipjtixnxawnyzlveeuzcsqhvmzidvzocpcdhduxwqmbocvbsurqoownlhgorhialggnndyszyvirungqwtthgxpvbwepvzijjotspxbktxqzxjszayzelftbqbuhtbvxzjvyrwbzwvuhhiiixzbsousjxnzrsidmgxuhfkhfqgaurzqnmemxrhowvwkytxcpbfradifcjvtxegkrnnchyhewmsqigtosskmljhsfctpgyxfkgfqjbrtxpyvxwjggzkogcsfyjjjggymudtwrxdzhmcxcaoyxwyqmrrgxarkyukidvolndvhsloyamnmpmkbkrtzckdultyhviwkeimpqfsrmsbmwutyajbqjzifynyrbycmfzogqndclohhlmrylfhmtfciisajwbkqtmrxzwftprsmzxxvhrvvleimebidybzqgjpjxngsbmlushivyummzeruxwbmleqiidxusdkhbyhwxdlyebmmwdkmpfymbltjmacleuabgattoxelojvjfuzkg"};
    str = strip_text(str);


    std::string buffer {};
    for(char c: str){
        char c1 = rotor_box.convert_char(c);
        std::cout << static_cast<char>(toupper(c1));
        buffer += c1;
    }
    std::cout << std::endl;

    std::ofstream file {};
    file.open("raw_output.txt");
    file << buffer;
    file.close();

    std::cout << "Done" << std::endl;

    return 0;
}
