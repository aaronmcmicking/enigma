//
// Created by aaron on 2023-06-22.
//

#ifndef ENIGMA_OP_H
#define ENIGMA_OP_H

#include <string>
#include <fstream>

#ifndef MAX_INPUT_STRING_LENGTH
#define MAX_INPUT_STRING_LENGTH (40*1000)
#endif

namespace Op{
    inline void format_input_file(const std::string& filename);
    inline std::string format_text(const std::string& str);
    inline char* load_from_file(const std::string& filename, int* size_ptr); // allocates, but DOES NOT deallocate memory
    inline int ctoi(char c);
    inline char itoc(int i);

    template<typename T>
    inline void rep_arr(T* dest, const T* src, int size);
    template<typename T>
    inline void rep_arr3(T* dest, const T* src);
    template<typename T>
    inline void rep_arr3(T* dest, T a, T b, T c);
}

#ifndef OP_IMPLEMENT
#define OP_IMPLEMENT
#endif
#ifdef OP_IMPLEMENT
template <typename T>
void Op::rep_arr3(T* dest, const T *src) {
    for (int i{0}; i < 3; i++){ dest[i] = src[i]; }
}

template <typename T>
void Op::rep_arr3(T* dest, T a, T b, T c) {
    int src[]{a, b, c};
    for(int i {0}; i < 3; i++){ dest[i] = src[i]; }
}

template <typename T>
void Op::rep_arr(T *dest, const T *src, int size) {
    for (int i{0}; i < size; i++){ dest[i] = src[i]; }
}

int Op::ctoi(char c) { return tolower(c) - 'a' + 1; }

char Op::itoc(int i) { return static_cast<char>(i + 'a' - 1); }

void Op::format_input_file(const std::string &filename) {
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

std::string Op::format_text(const std::string &str) {
    std::string dest{};
    for (char c: str) {
        if (isalpha(c)) {
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

char* Op::load_from_file(const std::string& filename, int* size_ptr){
    Op::format_input_file(filename);

    char* buf {new char[MAX_INPUT_STRING_LENGTH]};
    std::ifstream file {filename};
    file.get(buf, MAX_INPUT_STRING_LENGTH);

    if(size_ptr != nullptr) {
        int count{0};
        for (int i{0}; buf[i] != '\0'; i++) count++;
        *size_ptr = count;
//        std::cout << "got size_ptr = " << count << std::endl;
    }

    return buf;
}
#endif // OP_IMPLEMENT

#endif //ENIGMA_OP_H
