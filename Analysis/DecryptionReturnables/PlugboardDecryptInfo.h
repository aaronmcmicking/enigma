//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_PLUGBOARDDECRYPTINFO_H
#define ENIGMA_PLUGBOARDDECRYPTINFO_H


#include "RingDecryptInfo.h"
#include <iostream>
#include <iomanip>

// Stores results from plugboard decryption as well as the ring position decryption information used to attain this info
class PlugboardDecryptInfo: public DecryptInfo{
public:
    RingDecryptInfo ring_info;
    std::string plugboard;
    Op::Method method;
//    long double fitness;

    /*   Semantics    */
    // default constructor
    PlugboardDecryptInfo();

    // fielded constructor
    PlugboardDecryptInfo(const RingDecryptInfo& rinfo, std::string  new_plugboard, Op::Method new_method, long double new_fitness);

    // copy constructor
    PlugboardDecryptInfo(const PlugboardDecryptInfo& other);

    // destructor
    ~PlugboardDecryptInfo() override; // default

    // assignment operator
    PlugboardDecryptInfo& operator=(const PlugboardDecryptInfo& other);


    /* Functional */
    // prints the formatted contents of this instance
    void print(bool header) const override;
    void print() const override; // wrapper for print(false)

    /**
     * Defines weak ordering for lists of PlugboardDecryptInfo objects. An object should come first in a list if
     * it's `fitness` field is higher. If both items have the same fitness, `this` is ordered before `other`.
     * @param other The object to strict_weak_ordering this object to.
     * @return True if this object should be ordered before `other`, false otherwise.
     */
    [[nodiscard]] bool compare(const PlugboardDecryptInfo& other) const;

    /**
    * Defines weak ordering for lists of PlugboardDecryptInfo objects. An item should come first in a list if
    * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
    * @param first The first item to strict_weak_ordering.
    * @param second The second item to strict_weak_ordering.
    * @return True if `first` is ordered before `second`, false otherwise.
    */
    [[nodiscard]] static bool strict_weak_ordering(const RingDecryptInfo& first, const RingDecryptInfo& second);
};


#endif //ENIGMA_PLUGBOARDDECRYPTINFO_H
