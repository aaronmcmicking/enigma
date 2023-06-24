//
// Created by aaron on 2023-06-05.
//

#ifndef ENIGMA_ENIGMAMACHINE_H
#define ENIGMA_ENIGMAMACHINE_H


#include "RotorBox.h"
#include "Plugboard.h"

/*
 * EnigmaConfig stores a set of settings for an EnigmaMachine. Can be used to store config info and set it in a given
 * EnigmaMachine at any given time.
 */
typedef struct{
    int rotors[3];
    int rotor_pos[3];
    int ring_pos[3];
    char reflector;
    std::string plugboard;
}EnigmaConfig;

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
    EnigmaMachine(); // may not be instantiated without proper fields

    // converts a character through the plugboard and rotor box
    int convert_char(char c);
public:
    EnigmaMachine(int rotors[3], int rotor_pos[3], int ring_pos[3], char reflector, const std::string& plugboard);

    // `config` should be fully instantiated with values
    explicit EnigmaMachine(EnigmaConfig config);

    // Encrypts the contents of `in`
    // Returns the encrypted data
    std::string encrypt_or_decrypt_str(const std::string& in);

    // Encrypts `n` characters from `src` and stores it `dest`
    void encrypt_or_decrypt_arr(char* dest, const char* src, int size);

//    void encrypt_or_decrypt_arr_direct(char *dest, const char *src, int size); // doesn't call convert_char(c)

    /*
    * Encrypts or decrypts  'n' characters from `src` and stores them in `dest`. `src` need not be a c-style string.
    * Removes some function calls by removing some safety
    * checks and performing logic itself at risk of becoming outdated when some methods are updated (done to increase
    * performance).
    */
    void encrypt_or_decrypt_arr_direct(char *dest, const char *src, int size); // doesn't call convert_char(c)

    /* Encrypts or decrypts  characters from `src` and stores them in `dest` until a null terminator is encountered in `src`. Therefore,
    * `src` MUST be a c-style string.
    * Improves performance by removing some safety checks and performing logic itself to remove function calls at risk
     * of processing bad data or becoming outdated when some methods are updated.
    */
    void encrypt_or_decrypt_arr_direct(char *dest, const char* src);

    /*
     * Encrypts or decrypts the contents of `in_file_path` and stores the result in `out_file_path`.
     */
    void encrypt_or_decrypt_file(const std::string& in_file_path, const std::string& out_file_path); // true if success, false otherwise

    // Sets the rotors installed in the rotor box in the order they appear in `rotors`. `rotors` must have length 3.
    void set_rotors(const int* rotors);

    // Sets the rotor positions installed in the rotor box in the order they appear in `pos`. `pos` must have length 3.
    void set_rotor_pos(const int* pos);

    // Sets the rotor ring positions installed in the rotor box in the order they appear in `ring`. `ring` must have length 3.
    void set_ring_pos(const int* ring_pos);

    // Sets the reflector installed in the rotor box.
    void set_reflector(char c);

    // Sets the plugboard installed in the rotor box. See Plugboard.h for more information of plugboard formatting.
    void set_plugboard_settings(const std::string& settings);

    // Returns the current plugboard
    Plugboard& get_plugboard();

    // Sets the current configuration using an EngimaConfig object.
    void set_config(const EnigmaConfig& config);

    // [[ CURRENTLY UNIMPLEMENTED ]]
    // Prints the current configuration of the Enigma Machine
    [[maybe_unused]] void print_config();

    // Prints the configuration stored in an EnigmaConfig object
    static void print_config_object(const EnigmaConfig& config);

    // Copies all the data from `src` into `dest`. Allocates new memory for `dest` such that `src` and `dest` will not
    // share state
    static void copy_config(EnigmaConfig& dest, EnigmaConfig& src);
};


#endif //ENIGMA_ENIGMAMACHINE_H
