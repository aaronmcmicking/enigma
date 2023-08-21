//
// Created by aaron on 2023-06-02.
//

#ifndef ENIGMA_STDEO_H
#define ENIGMA_STDEO_H

#include <utility>
#include <string>

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

/*
 * Contains common operations throughout EnigmaMachine for convenience.
 */
namespace stdeo { // "stdeo" = Standard Enigma Operations
    // contract for templates to be an arithmetic type
    template<typename T>
    concept arithmetic_type = std::integral<T> or std::floating_point<T>;

    // Converts a letter into its 1-indexed position in the alphabet (ie. 'a' -> 1, 'c' -> 3, `z` -> 26, etc.)
    inline int ctoi(char c);

    // Converts a letter from its 1-indexed position in the alphabet to its lowercase integer representation
    // (ie. 3 -> 'c', 25 -> 'y', etc.)
    inline char itoc(int i);

    // Returns true if  min <= num <= max,  false otherwise
    template<typename T> requires arithmetic_type<T>
    inline bool is_in_range(T num, T min, int max);

    // Returns string of lowercase version of all alphabetical characters in `str`
    // ie. "KM47 ==- 1294 H7HY';235"  -->  "kmhhy"
    inline std::string strip_text(const std::string& str);

    // Copies first n (arrncpy) or three (arrcpy3) elements of src into dest
    template<typename T>
    inline void arrncpy(T* dest, T* src, int n);
    template<typename T>
    inline void arrcpy3(T dest[3], const T* src);
    template<typename T>
    inline void arrcpy3(T dest[3], T a, T b, T c);
}

#ifndef STDEO_IMPLEMENT
#define STDEO_IMPLEMENT
#endif
#ifdef STDEO_IMPLEMENT
int stdeo::ctoi(char c) {
    return (tolower(c) - 'a' + 1);
}

char stdeo::itoc(int i) {
    return static_cast<char>(i + 'a' - 1);
}

std::string stdeo::strip_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

// inclusive
template<typename T> requires stdeo::arithmetic_type<T>
bool stdeo::is_in_range(T num, T min, int max){
    return (num >= min) && (num <= max);
}

template<typename T>
inline void stdeo::arrncpy(T* dest, T* src, int n){
    for(int i {}; i < n; i++){
        dest[i] = src[i];
    }
}

template<typename T>
void stdeo::arrcpy3(T dest[3], const T* src){
    for(int i {0}; i < 3; i++) dest[i] = src[i];
}

template<typename T>
void stdeo::arrcpy3(T dest[3], T a, T b, T c){
    T src[] {a, b, c};
    arrcpy3(dest, src);
}

#endif // STDEO_IMPLEMENT

#endif //ENIGMA_STDEO_H
