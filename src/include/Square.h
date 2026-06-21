#pragma once 

#include <string> 
#include <cstring>
#include <stdint.h>

class Square{
    /*
    Square class represents a square on the chess board. It is essentially a
    wrapper for an int8_t from 0 to 63, where 0 represents a1 and 63 represents h8. 
    Extra function added for operator overload for string comparison, so that we can 
    easily convert between file/rank (as either int8_ts or as chars / string) and 
    square index (int8_t).
    */
    int8_t index = INT8_MAX; // 0-63, where 0 is a1 and 63 is h8
    public: 

    Square(const int8_t file, const int8_t rank);
    Square(const int8_t new_index = INT8_MAX);
    explicit Square(const std::string& square_str);
    Square& operator=(const Square& other);
    Square& operator=(const int8_t& new_index);
    void set_square(const int8_t file, const int8_t rank);
    void set_square(const int8_t new_index);
    inline int8_t operator()() const {return index;};
    operator int() const;
    bool operator==(const std::string& other) const;
    bool operator==(const char *other) const;
    inline bool operator==(const Square& other) const {return index == other.index;};
    inline bool operator==(const int8_t& other) const {return index == other;};
    inline int8_t file() const {return index % 8;}
    inline int8_t rank() const {return index / 8;}
    void inc_file() {this->apply_offset(1, 0, true);}
    void dec_file() {this->apply_offset(-1, 0, true);}
    void inc_rank() {this->apply_offset(0, 1, true);}
    void dec_rank() {this->apply_offset(0, -1, true);}
    Square apply_offset(const int file_offset, const int rank_offset, bool inplace = false);
    inline bool in_bounds() const {return (index >= 0 && index <= 63);}
    std::string to_string() const;

};