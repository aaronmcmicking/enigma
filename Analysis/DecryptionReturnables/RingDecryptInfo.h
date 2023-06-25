//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_RINGDECRYPTINFO_H
#define ENIGMA_RINGDECRYPTINFO_H

#include "RotorDecryptInfo.h"

// Stores results from ring position decrypt as well as the rotor decryption information used to attain this info
class RingDecryptInfo{
public:
    RotorDecryptInfo rotor_info {};
    int* ring_pos;
    Op::Method method;
    long double fitness;

    /* Semantic */
    // default constructor
    RingDecryptInfo();

    // fielded constructor
    RingDecryptInfo(const RotorDecryptInfo& rinfo, int* new_ring_pos, Op::Method new_method, long double new_fitness);

    // copy constructor
    RingDecryptInfo(const RingDecryptInfo& other);

    // destructor
    ~RingDecryptInfo();

    // assignment operator
    RingDecryptInfo& operator=(const RingDecryptInfo& other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const;
    void print() const;

    /**
     * Defines weak ordering for lists of RingDecryptInfo objects. An object should come first in a list if
     * it's `fitness` field is higher. If both items have the same fitness, `this` is ordered before `other`.
     * @param other The object to strict_weak_ordering this object to.
     * @return True if this object should be ordered before `other`, false otherwise.
     */
    [[nodiscard]] bool compare(const RingDecryptInfo& other) const;

    /**
    * Defines weak ordering for lists of RingDecryptInfo objects. An item should come first in a list if
    * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
    * @param first The first item to strict_weak_ordering.
    * @param second The second item to strict_weak_ordering.
    * @return True if `first` is ordered before `second`, false otherwise.
    */
    [[nodiscard]] static bool strict_weak_ordering(const RingDecryptInfo& first, const RingDecryptInfo& second);
};


#endif //ENIGMA_RINGDECRYPTINFO_H
