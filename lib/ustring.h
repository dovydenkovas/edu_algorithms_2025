#pragma once
#include "vector.h"
#include <algorithm>
#include <cstdint>
#include <ostream>


class ustring {
    vector<uint32_t> characters;

public:
    ustring(const char *str);
    ustring(const ustring& str);
    ustring(ustring&& str);

    uint32_t& operator[](size_t index) {return characters[index];};
    uint32_t operator[](size_t index) const {return characters[index];};

    ustring& operator=(const ustring &str);
    ustring& operator=(ustring &&str);

    ustring& operator+=(ustring &str);
    size_t size() {return characters.size();}

    vector<uint32_t>::iterator begin() {return characters.begin();};
    vector<uint32_t>::iterator end() {return characters.end();};
};


/**
 * Определяет длину utf8 символа в байтах.
 */
int char_length(const char *str, const int index) {
    if ((str[index] >> 7 & 1) == 0)
        return 1;
    if ((str[index] >> 5 & 7) == 6)
        return 2;
    if ((str[index] >> 4 & 15) == 14)
        return 3;
    if ((str[index] >> 3 & 31) == 30)
        return 4;
    if ((str[index] >> 6 & 3) == 2)
        throw "Not the head byte of character";
    throw "Unknown character";
}

/*
 * Декодирует utf8 символ в его unicode номер.
 */
uint32_t decode_utf8(const char* str, const int index, const int size) {
    if (size == 1)
        return str[index];
    if (size == 2)
        return ((str[index]   & 0b0001'1111) << 6)
             | ((str[index+1] & 0b0011'1111));

    if (size == 3)
        return ((((str[index] & 0b0000'1111) << 6)
              | ((str[index+1] & 0b0011'1111))) << 6)
              | (str[index+2] & 0b0011'1111);

    return ((((((str[index] & 0b0000'0111) << 6)
             | ((str[index+1] & 0b0011'1111))) << 6)
             |  (str[index+2] & 0b0011'1111)) << 6)
             |  (str[index+3] & 0b0011'1111);
}


ustring::ustring(const char* str) {
    int i = 0;
    int current_index = 0;
    while (str[i] != 0) {
        int size = char_length(str, i);
        characters.push_back(decode_utf8(str, i, size));
        ++current_index;
        i += size;
    }
}

ustring::ustring(const ustring& str)
{
    characters = str.characters;
}

ustring::ustring(ustring&& str)
{
    characters = std::move(characters);
}

ustring& ustring::operator=(const ustring &str)
{
    characters = str.characters;
    return *this;
}

ustring& ustring::operator=(ustring &&str)
{
    characters = std::move(str.characters);
    return *this;
}

ustring& ustring::operator+=(ustring &str)
{
    for (auto &ch: str.characters)
        characters.push_back(ch);
    return *this;
}


std::ostream& operator<<(std::ostream &os, ustring str)
{
    for (auto &ch: str)
        os << ch << ' ';
    return os;
}
