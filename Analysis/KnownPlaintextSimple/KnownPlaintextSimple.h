//
// Created by aaron on 2023-06-17.
//

#ifndef ENIGMA_KNOWNPLAINTEXTSIMPLE_H
#define ENIGMA_KNOWNPLAINTEXTSIMPLE_H


class KnownPlaintextSimple {
public:
    static int calculate(const char* decrypted_text, long d_size, const char* plaintext, long p_size, int offset);
};


#endif //ENIGMA_KNOWNPLAINTEXTSIMPLE_H
