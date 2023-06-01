//
// Created by aaron on 2023-06-01.
//

#include "RotorBox.h"
#include "RotorMappingBuilder.h"

RotorBox::RotorBox(): rotors_in_place {new Rotor[] {RotorI, RotorII, RotorIII}}{
    RotorMappingBuilder::set_init(false);
    RotorMappingBuilder::nullify_mappings();
    std::map<int, int> mapI = RotorMappingBuilder::get_rotor_mapping(1);
    std::map<int, int> mapII = RotorMappingBuilder::get_rotor_mapping(2);
    std::map<int, int> mapIII = RotorMappingBuilder::get_rotor_mapping(3);
    std::map<int, int> mapIV = RotorMappingBuilder::get_rotor_mapping(4);
    std::map<int, int> mapV = RotorMappingBuilder::get_rotor_mapping(5);
    std::map<int, int> mapVI = RotorMappingBuilder::get_rotor_mapping(6);
    std::map<int, int> mapVII = RotorMappingBuilder::get_rotor_mapping(7);
    std::map<int, int> mapVIII = RotorMappingBuilder::get_rotor_mapping(8);

    RotorI.set_mappings(mapI);
    RotorI.set_turnover_position( RotorMappingBuilder::ctoi('r') );

    RotorII.set_mappings(mapII);
    RotorI.set_turnover_position( RotorMappingBuilder::ctoi('f') );

    RotorIII.set_mappings(mapIII);
    RotorIII.set_turnover_position( RotorMappingBuilder::ctoi('w') );

    RotorIV.set_mappings(mapIV);
    RotorIV.set_turnover_position( RotorMappingBuilder::ctoi('k') );

    RotorV.set_mappings(mapV);
    RotorV.set_turnover_position( RotorMappingBuilder::ctoi('a') );

    // these rotors should have 2 turnovers each (at 'a' and 'n'), but this is not currently supported
    RotorVI.set_mappings(mapVI);
    RotorVII.set_mappings(mapVII);
    RotorVIII.set_mappings(mapVIII);
    RotorVI.set_turnover_position( RotorMappingBuilder::ctoi('a') );
    RotorVII.set_turnover_position( RotorMappingBuilder::ctoi('a') );
    RotorVIII.set_turnover_position( RotorMappingBuilder::ctoi('a') );
}

Rotor RotorBox::get_rotor(int rotor_number){
    Rotor rotors[] {RotorI, RotorII, RotorIII, RotorIV, RotorV, RotorVI,RotorVII, RotorVIII};
    return rotors[rotor_number-1];
}

Rotor* RotorBox::get_all_rotors(){
    return new Rotor[] {RotorI, RotorII, RotorIII, RotorIV, RotorV, RotorVI, RotorVII, RotorVIII};
}

void RotorBox::set_placed_rotor(int rotor_number, int position){
    rotors_in_place[position-1] = get_rotor(rotor_number);
}