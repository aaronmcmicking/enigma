//
// Created by aaron on 2023-06-17.
//

#ifndef ENIGMA_KNOWNPLAINTEXTSIMPLE_H
#define ENIGMA_KNOWNPLAINTEXTSIMPLE_H

/*
 * Simple known-plaintext fitness function that yields very meh results.
 */
class KnownPlaintextSimple {
public:
    // calculates fitness using known-plaintext
    // i think this may be broken right now? it was never effective enough for me to care to properly debug it
    static int calculate(const char* decrypted_text, long d_size, const char* plaintext, long p_size, int offset);
};


#endif //ENIGMA_KNOWNPLAINTEXTSIMPLE_H
