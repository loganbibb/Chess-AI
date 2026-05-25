#pragma once 

#include <string> 
#include <cstring>
#include <stdint.h>

class Square{
    /*
    Square class represents a square on the chess board. It is essentially a
    wrapper for a uint8_t from 0 to 63, where 0 represents a1 and 63 represents h8. 
    Extra function added for operator overload for string comparison, so that we can 
    easily convert between file/rank (as either uint8_ts or as chars / string) and 
    square index (uint8_t).
    */
    uint8_t index = UINT8_MAX; // 0-63, where 0 is a1 and 63 is h8
    public: 

    Square(const uint8_t file, const uint8_t rank);
    Square(const uint8_t new_index);
    Square(const char *square_str);
    Square& operator=(const Square& other);
    Square& operator=(const uint8_t& new_index);
    void set_square(const uint8_t file, const uint8_t rank);
    void set_square(const uint8_t new_index);
    inline uint8_t file() const {return index % 8;}
    inline uint8_t rank() const {return index / 8;}
    uint8_t operator()() const;
    bool operator==(const std::string& other) const;
    bool operator==(const char *other) const;
    bool operator==(const Square& other) const;
    operator int() const;
    std::string to_string() const;

};