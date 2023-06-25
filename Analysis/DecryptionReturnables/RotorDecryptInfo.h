//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_ROTORDECRYPTINFO_H
#define ENIGMA_ROTORDECRYPTINFO_H

#include "../Op.h"
#include "DecryptInfo.h"

// Stores result from rotor decryption
class RotorDecryptInfo: public DecryptInfo{
public:
    int* rotors;
    int* rotor_pos;
    char reflector;
    Op::Method method;
//    long double fitness;

    /* Semantic */
    // default constructor
    RotorDecryptInfo();

    // fielded constructor
    RotorDecryptInfo(int* new_rotors, int* new_rotor_pos, char ref, Op::Method new_method, long double new_fitness);

    // copy constructor
    RotorDecryptInfo(const RotorDecryptInfo &other);

    // destructor
    ~RotorDecryptInfo();

    // copy assignment operator
    RotorDecryptInfo &operator=(const RotorDecryptInfo &other);


    /* Functional */
    // prints the formatted contents of this instance
    void print() const override; // wraps print(bool)

    void print(bool header) const override;

    /**
     * Defines weak ordering for lists of RotorDecryptInfo objects. An object should come first in a list if
     * it's `fitness` field is higher. If both items have the same fitness, `this` is ordered before `other`.
     * @param other The object to strict_weak_ordering this object to.
     * @return True if this object should be ordered before `other`, false otherwise.
     */
    [[nodiscard]] bool compare(const RotorDecryptInfo& other) const;

    /**
    * Defines weak ordering for lists of BlindDecrypt::RotorDecryptInfo structs. An item should come first in a list if
    * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
    * @param first The first item to strict_weak_ordering.
    * @param second The second item to strict_weak_ordering.
    * @return True if `first` is ordered before `second`, false otherwise.
    */
    [[nodiscard]] static bool strict_weak_ordering(const RotorDecryptInfo& first, const RotorDecryptInfo& second);
};


#endif //ENIGMA_ROTORDECRYPTINFO_H
