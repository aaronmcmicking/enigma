//
// Created by aaron on 2023-06-05.
//

#ifndef ENIGMA_ENIGMAMACHINE_H
#define ENIGMA_ENIGMAMACHINE_H


#include "RotorBox.h"
#include "Plugboard.h"

typedef struct{
    int rotors[3];
    int rotor_pos[3];
    int ring_pos[3];
    char reflector;
    std::string plugboard;
}EnigmaConfig;

class EnigmaMachine {
private:
    RotorBox rotor_box;
    Plugboard plugboard;

    EnigmaMachine(); // may not be instantiated without proper fields

    int convert_char(char c);
public:
    EnigmaMachine(int rotors[3], int rotor_pos[3], int ring_pos[3], char reflector, const std::string& plugboard);

    explicit EnigmaMachine(EnigmaConfig config);

    std::string encrypt_or_decrypt_str(const std::string& in);

    void encrypt_or_decrypt_arr(char* dest, char* src, int size);

//    void encrypt_or_decrypt_arr_direct(char *dest, const char *src, int size); // doesn't call convert_char(c)

    void encrypt_or_decrypt_arr_direct(char *dest, const char *src, int size); // doesn't call convert_char(c)

    void encrypt_or_decrypt_arr_direct(char *dest, const char* src);

    bool encrypt_or_decrypt_file(const std::string& in_file_name, const std::string& out_file_name); // true if success, false otherwise

    void set_rotors(const int* rotors);

    void set_rotor_pos(const int* pos);

    void set_ring_pos(const int* ring_pos);

    void set_reflector(char c);

    void set_plugboard_settings(const std::string& settings);

    Plugboard& get_plugboard();

    void set_config(const EnigmaConfig& config);

    void print_config();

    static void print_config_object(const EnigmaConfig& config);

    static void copy_config(EnigmaConfig& dest, EnigmaConfig& src);
};


#endif //ENIGMA_ENIGMAMACHINE_H
