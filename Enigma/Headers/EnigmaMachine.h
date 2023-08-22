//
// Created by aaron on 2023-06-05.
//

#ifndef ENIGMA_ENIGMAMACHINE_H
#define ENIGMA_ENIGMAMACHINE_H


#include "RotorBox.h"
#include "Plugboard.h"
#include "EnigmaConfig.h"


/*
 * An EnigmaMachine contains a RotorBox and a Plugboard and models the functionality of its real-life counterpart
 *
 * An EnigmaMachine may never be instantiated without providing content for the RotorBox and Plugboard. Constructors
 * for this information exist using individual fields and with just an instance of EnigmaConfig
 */
class EnigmaMachine {
private:
    RotorBox rotor_box; // The rotor box
    Plugboard plugboard; // The plugboard

    // An EnigmaMachine may not be instantiated without proper fields.
    EnigmaMachine(); 

    // converts a character through the plugboard and rotor box
    int convert_char(char c);
public:
    EnigmaMachine(int rotors[3], int rotor_pos[3], int ring_pos[3], char reflector, const std::string& plugboard);

    // `config` should be fully instantiated with values
    explicit EnigmaMachine(const EnigmaConfig& config);

    // Incrypts the contents of `in` and returns the result
    std::string encrypt_or_decrypt(const std::string& in);

    // Encrypts `n` characters from `src` and stores it `dest`
    void encrypt_or_decrypt(char* dest, const char* src, int size);

    // Encrypts or decrypts the contents of `in_file_path` and stores the result in `out_file_path`.
    void encrypt_or_decrypt(const std::string& in_file_path, const std::string& out_file_path); 

    /*
    * Encrypts or decrypts  'n' characters from `src` and stores them in `dest`. `src` need not be a C-style string.
    * Removes calls to common functions to improve performance, thereby becoming
    * unsafe since assumptions about the behaviour of the common functions may
    * become outdated.
    */
    void encrypt_or_decrypt_fast(char *dest, const char *src, int size); // doesn't call convert_char(c)

    /* Encrypts or decrypts  characters from `src` and stores them in `dest` 
    * until a null terminator is encountered in `src`. Therefore, `src` MUST be 
    * a C-style string. Removes calls to common functions to improve performance, 
    * thereby becoming unsafe since assumptions about the behaviour of the 
    * common functions may become outdated.
    */
    void encrypt_or_decrypt_fast(char *dest, const char* src);

    void set_rotors(const int* rotors);

    void set_rotor_pos(const int* pos);

    void set_ring_pos(const int* ring_pos);

    void set_reflector(char c);

    // See Plugboard.h for more information of plugboard formatting.
    void set_plugboard_settings(const std::string& settings);

    Plugboard& get_plugboard();

    void set_config(const EnigmaConfig& config);

    // [[ CURRENTLY UNIMPLEMENTED ]]
    // Prints the current configuration of the Enigma Machine
    [[maybe_unused]] void print_config();

    // Prints the configuration stored in an EnigmaConfig object
    // OBSOLETE: USE EnigmaConfig::print
    static void print_config_object(const EnigmaConfig& config);

    // Copies all the data from `src` into `dest`. Allocates new memory for `dest` such that `src` and `dest` will not
    // share state
    // OBSOLETE: USE EnigmaConfig::operator=
    static void copy_config(EnigmaConfig& dest, EnigmaConfig& src);
};


#endif //ENIGMA_ENIGMAMACHINE_H
