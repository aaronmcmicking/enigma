#include <iostream>
#include "RotorBox.h"

int main(){
    RotorBox rotor_box {};
//    Rotor* r_arr {rotor_box.get_all_rotors()};
//    for(int i = 0; i < 8; i++){
//        r_arr[i].print_rotor_mappings();
//    }

    std::cout << "Testing rotors" << std::endl;

    for(int i = 0; i < 26*26 + 10; i++) {
        std::cout << rotor_box.convert_char_through_rotors('a') << std::endl;
        Rotor* r = rotor_box.get_rotors_in_place();
//        if(i > 26*25) {
//            for (int w = 0; w < 3; w++) {
//                std::cout << "rotor " << w + 1 << ":  pos = " << r[w].get_position() << "  |  turnover_pos = "
//                          << r[w].get_turnover_position() << std::endl;
//            }
//        }
    }

    return 0;
}
