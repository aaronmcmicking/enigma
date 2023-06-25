//
// Created by aaron on 2023-06-24.
//

#ifndef ENIGMA_DECRYPTINFO_H
#define ENIGMA_DECRYPTINFO_H

class DecryptInfo{
public:
    long double fitness;

    constexpr DecryptInfo(): fitness {} { }

    virtual ~DecryptInfo() = default;

    explicit DecryptInfo(long double new_fitness): fitness {new_fitness} { }

    virtual void print(bool header) const = 0;
    virtual void print() const = 0;
};


#endif //ENIGMA_DECRYPTINFO_H
