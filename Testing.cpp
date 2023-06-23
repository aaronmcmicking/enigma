//
// Created by aaron on 2023-06-22.
//

#include <iostream>
#include <chrono>
#include "Enigma/Headers/EnigmaMachine.h"
#include "Analysis/Op.h"

namespace EMFunctionTesting{

    inline int main(){

        EnigmaConfig encrypt_config {
            .rotors {2, 5, 3},
            .rotor_pos{21, 19, 6},
            .ring_pos{9, 22, 17},
            .reflector = 'B',
            .plugboard {"JM HO PQ LD UG ZF KS AN BX YW"}
        };

        EnigmaMachine em {encrypt_config};

        int size {};
        char* e_text {Op::load_from_file(R"(J:\Programming\enigma\cmake-build-debug\in_out\plaintext.txt)", &size)};
        char* d_text {new char[size+1]};


        long long avg {};
        int count{50000};
        int passes{10};
        auto start_time {std::chrono::high_resolution_clock::now()};

        for(int w {}; w < passes; w++){
            start_time = std::chrono::high_resolution_clock ::now();
            for(int i{}; i < count; i++){
                em.encrypt_or_decrypt_arr_direct(d_text, e_text, size);
            }

            auto end_time{std::chrono::high_resolution_clock::now()};
            auto dur{duration_cast<std::chrono::microseconds>(end_time - start_time)};

            avg += dur.count();

            std::cout << count << " iterations took " << dur.count() / 1000ll << " milliseconds (average = "
                      << (dur.count() / count) << " microseconds)" << std::endl;
        }

        std::cout << passes << " passes took " << avg / 1000ll << " milliseconds (average = "
                << (avg / passes) << " microseconds)" << std::endl;



        avg = 0;
        for(int w {}; w < passes; w++){
            start_time = std::chrono::high_resolution_clock ::now();
            for(int i{}; i < count; i++){
                em.encrypt_or_decrypt_arr_direct(d_text, e_text, size);
            }

            auto end_time{std::chrono::high_resolution_clock::now()};
            auto dur{duration_cast<std::chrono::microseconds>(end_time - start_time)};

            avg += dur.count();

            std::cout << count << " iterations took " << dur.count() / 1000ll << " milliseconds (average = "
                      << (dur.count() / count) << " microseconds)" << std::endl;
        }

        std::cout << passes << " passes took " << avg / 1000ll << " milliseconds (average = "
                  << (avg / passes) << " microseconds)" << std::endl;


        std::cout << e_text << std::endl;

        return 0;
    }

}