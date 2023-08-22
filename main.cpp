#include "Analysis/BlindDecrypt.h"
#include "Analysis/stdo.h"
#include "Enigma/Headers/EnigmaMachine.h"
#include "misc_debug.cpp"

int main(){

    /*
     * An example usage of an EnigmaMachine and encryption/decryption is shown 
     * here.
     */

    // Create an EnigmaConfig with new settings
    int rotors[]{2, 5, 3};
    int rotor_positions[]{21, 19, 6};
    int ring_settings[]{17, 25, 1};
    EnigmaConfig encrypt_config {
            rotors,
            rotor_positions,
            ring_settings,
            'B',
            "IK BH RG NA PF"
    };

    EnigmaMachine em {encrypt_config};

    const std::string plaintext {BlindDecrypt::default_plaintext_path};
    const std::string encrypted_text {BlindDecrypt::default_encrypted_path};
    const std::string decrypted_text {BlindDecrypt::default_decrypted_path};

    stdo::format_input_file(BlindDecrypt::default_plaintext_path);

    // Encrypt the plaintext file and store the result.
    em.encrypt_or_decrypt(plaintext, encrypted_text);

    // Decrypt the encrypted file.
    BlindDecrypt::decrypt(encrypted_text, decrypted_text, stdo::INDEX_OF_COINCIDENCE);

    return 0;
}

