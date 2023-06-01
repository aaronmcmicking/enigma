#include <iostream>
#include "RotorBox.h"

int main(){
    RotorBox rotor_box {};
    Rotor* r_arr {rotor_box.get_all_rotors()};
    for(int i = 0; i < 8; i++){
        r_arr[i].print_rotor_mappings();
    }
    return 0;
}