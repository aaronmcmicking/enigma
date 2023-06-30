//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_DECRYPTINFO_H
#define ENIGMA_DECRYPTINFO_H

#include "../../Enigma/Headers/EnigmaConfig.h"

class DecryptInfo{
public:
    long double fitness;

    constexpr DecryptInfo(): fitness {} { }

    virtual ~DecryptInfo() = default;

    explicit DecryptInfo(long double new_fitness): fitness {new_fitness} { }

    virtual void print(bool header) const = 0;
    virtual void print() const = 0; // usually wraps print(false)

    [[nodiscard]] virtual EnigmaConfig to_config() const = 0;
    virtual void to_config(EnigmaConfig& config) const = 0;

    /**
     * Defines weak ordering for lists of DecryptInfo objects. An object should come first in a list if
     * it's `fitness` field is higher. If both items have the same fitness, `this` is ordered before `other`.
     * @param other The object to strict_weak_ordering this object to.
     * @return True if this object should be ordered before `other`, false otherwise.
     */

    [[nodiscard]] virtual bool compare(const DecryptInfo& other) const{
        return fitness >= other.fitness;
    }

    /**
    * Defines weak ordering for DecryptInfo objects. An object should come first in a list if
    * it's `fitness` field is higher. If both items have the same fitness, `first` is ordered before `second`.
     * <br><br>
     * The intended use-case for this function is to be used to order subclass objects in lists, including by passing
     * this function as a parameter.
    * @param first The first item to compare.
    * @param second The second item to compare.
    * @return true if `first` is ordered before `second`, false otherwise.
    */
    [[nodiscard]] __attribute__ ((pure)) static bool strict_weak_ordering(const DecryptInfo& first, const DecryptInfo& second){
        return first.fitness >= second.fitness;
    }
};


#endif //ENIGMA_DECRYPTINFO_H
