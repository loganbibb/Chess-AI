#include <string> 
#include <cstring>
#include <stdint.h>

#include "include/error_types.h"
#include "include/Square.h"

Square::Square(uint8_t file, uint8_t rank) {
    // file is 0-7, where 0 is a and 7 is h. rank is 0-7, where 0 is 1 and 7 is 8.
    index = rank * 8 + file;
}

Square::Square(uint8_t new_index) {
    index = new_index;
}

Square::Square(const std::string& square_str) {
    // square_str is in the format of "a1", "e4", etc.
    if (square_str.length() != 2) {
        throw Exceptions::InvalidArgumentException("Invalid square string. Square string must be in the format of 'a1', 'e4', etc.");
    }
    uint8_t file = (uint8_t)(square_str[0] - 'a'); 
    uint8_t rank = (uint8_t)(square_str[1] - '1'); 
    index = rank * 8 + file;
}

Square& Square::operator=(const Square& other) {
    if (this == &other) {
        return *this; // handle self assignment
    }
    index = other.index;
    return *this;
}

Square& Square::operator=(const uint8_t& new_index) {
    index = new_index;
    return *this;
}

void Square::set_square(uint8_t file, uint8_t rank) {
    index = rank * 8 + file;
}

void Square::set_square(uint8_t new_index) {
    index = new_index;
}

uint8_t Square::operator()() const {
    return index;
}

bool Square::operator==(const std::string& other) const {
    // other is in the format of "a1", "e4", etc.
    if (other.length() != 2) {
        return false;
    }
    uint8_t other_file = other[0] - 'a'; 
    uint8_t other_rank = other[1] - '1'; 
    return file() == other_file && rank() == other_rank;
}

bool Square::operator==(const char *other) const {
    // other is in the format of "a1", "e4", etc.
    if (strlen(other) != 2) {
        return false;
    }
    uint8_t other_file = (uint8_t)(other[0] - 'a'); 
    uint8_t other_rank = (uint8_t)(other[1] - '1'); 
    return file() == other_file && rank() == other_rank;
}

bool Square::operator==(const Square& other) const {
    return index == other.index;
}

Square::operator int() const { return index; }

std::string Square::to_string() const {
    // convert from index to string format "a1", "e4", etc.
    char file_char = (char)('a' + file()); 
    char rank_char = (char)('1' + rank()); 
    return std::string(1, file_char) + std::string(1, rank_char);
}