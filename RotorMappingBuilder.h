//
// Created by aaron on 2023-06-01.
//

#ifndef ENIGMA_ROTORMAPPINGBUILDER_H
#define ENIGMA_ROTORMAPPINGBUILDER_H


class RotorMappingBuilder {
public:
    static bool init;
    static std::map<int, int>* rotor_mappings;

    static std::map<int, int> get_rotor_mapping(int rotor_number);

    // which = 'A' || 'B' || 'C'
    static std::map<int, int> get_reflector_mapping(char which);

    static void set_init(bool state);

    static void nullify_mappings();

private:
    static std::pair<int, int> pair(int k, int v);

    static void map_insert(std::map<int, int>& map, int k, char v);

    static void map_fill(std::map<int, int>& map, std::string vals);

    static std::map<int, int>* construct_rotor_mappings();

};

#endif //ENIGMA_ROTORMAPPINGBUILDER_H
