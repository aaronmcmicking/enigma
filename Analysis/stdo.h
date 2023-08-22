//
// Created by aaron on 2023-06-22.
//

#ifndef ENIGMA_STDO_H
#define ENIGMA_STDO_H

#include <string>
#include <fstream>

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

namespace stdo{ // "Standard Operations"
    // contract for templates to be an arithmetic type
    template<typename T>
    concept arithmetic_type = std::integral<T> or std::floating_point<T>;

    inline void format_input_file(const std::string& filename); // overwrites `filename` with the formatted version of its contents (see format_text(const string&)
    inline std::string format_text(const std::string& str); // returns all-lowercase string of the alphabetical characters in `str`

    /*
     * Both load_from_file(const string&, int*) and load_from_file(const string&) load text from `filename` and return
     * a pointer to an array containing those contents. The maximum number of characters that may be read is MAX_INPUT_STRING_LENGTH
     *
     * load_from_file(const string&, int*) stores the number of characters stored in return array (not including a
     * null-terminator) into *size_ptr
     *
     * Both functions allocate but do NOT deallocate memory.
     */
    inline char* load_from_file(const std::string& filename, int* size_ptr);
    inline char* load_from_file(const std::string& filename);

    inline int ctoi(char c); // Converts a character to its 1-indexed position in the alphabet (ie. 'A'->1, 'B'->2, etc)
    inline char itoc(int i); // Converts a letter from its 1-index position in the alphabet to its integer representation (inverse of ctoi(char c))
    inline std::string itor(int i); // Converts a number ( 1<= and <=9 ) to Roman Numerals.

    template<typename T> requires arithmetic_type<T>
    inline static T abs(T val); // absolute value

    template<typename T> requires arithmetic_type<T>
    inline bool is_in_range(T num, T min, T max); // Returns true if  min <= num <= max,  false otherwise

    /*
     * All functions below copy provided elements into `dest`
     */
    template<typename T>
    inline void arrncpy(T* dest, const T* src, int size);
    template<class T>
    inline void arrcpy(T* dest, std::initializer_list<T> elements); // allows variadic arguments as long as all elements have the same type
    template<typename T>
    inline void arrcpy3(T* dest, const T* src);
    template<typename T>
    inline void arrcpy3(T* dest, T a, T b, T c);

    // used to specify which statistical method should be used during a given decryption process
    enum Method{
        INDEX_OF_COINCIDENCE,
        CHARACTER_FREQUENCY,
    };
}

template <typename T>
void stdo::arrcpy3(T* dest, const T *src) {
    for (int i{0}; i < 3; i++){ dest[i] = src[i]; }
}

template <typename T>
void stdo::arrcpy3(T* dest, T a, T b, T c) {
    int src[]{a, b, c};
    for(int i {0}; i < 3; i++){ dest[i] = src[i]; }
}

template <typename T>
void stdo::arrncpy(T *dest, const T *src, int size) {
    for (int i{0}; i < size; i++){ dest[i] = src[i]; }
}

template<class T>
void stdo::arrcpy(T* dest, std::initializer_list<T> elements){
    for(uint64_t i {}; i < elements.size(); i++){
        dest[i] = elements[i];
    }
}

int stdo::ctoi(char c) { return tolower(c) - 'a' + 1; }

char stdo::itoc(int i) { return static_cast<char>(i + 'a' - 1); }

std::string stdo::itor(int i){
    if(!is_in_range(i, 1, 9)){
        return "INVALID_NUMERAL";
    }
    std::string str[] {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return str[i-1];
}

void stdo::format_input_file(const std::string &filename) {
    std::ifstream ifile{filename};

    char buf[MAX_INPUT_STRING_LENGTH]{};

    ifile.read(buf, MAX_INPUT_STRING_LENGTH);
    ifile.close();
    std::remove(filename.c_str());

    std::string buf2 = format_text(buf);

    std::ofstream ofile{filename};
    ofile << buf2;
    ofile.close();
}

std::string stdo::format_text(const std::string &str) {
    std::string dest{};
    for (char c: str) {
        if (isalpha(c)) {
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

char* stdo::load_from_file(const std::string& filename, int* size_ptr){
    stdo::format_input_file(filename);

    char* buf {new char[MAX_INPUT_STRING_LENGTH]};
    std::ifstream file {filename};
    file.get(buf, MAX_INPUT_STRING_LENGTH);

    if(size_ptr != nullptr) {
        int count{0};
        for (int i{0}; buf[i] != '\0'; i++) count++;
        *size_ptr = count;
    }

    return buf;
}

char* stdo::load_from_file(const std::string &filename){
    return load_from_file(filename, nullptr);
}

template<typename T> requires stdo::arithmetic_type<T>
T stdo::abs(T val){
    return val >= 0 ? val : -val;
}

template<typename T> requires stdo::arithmetic_type<T>
bool stdo::is_in_range(T num, T min, T max){
    return (num >= min) && (num <= max);
}


#endif //ENIGMA_STDO_H
