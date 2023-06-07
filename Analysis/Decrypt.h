//
// Created by aaron on 2023-06-06.
//

#ifndef ENIGMA_DECRYPT_H
#define ENIGMA_DECRYPT_H


class Decrypt {
public:
    enum Method{
        INDEX_OF_COINCIDENCE
    };

    static void decrypt(Method method);

};


#endif //ENIGMA_DECRYPT_H
