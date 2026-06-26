#include <string> 
#include <cstring>
#include <stdint.h>

#include "include/error_types.h"
#include "include/Square.h"

Square::Square(int8_t file, int8_t rank) {
    // file is 0-7, where 0 is a and 7 is h. rank is 0-7, where 0 is 1 and 7 is 8.
    index = rank * 8 + file;
}

Square::Square(int8_t new_index) {
    index = new_index;
}

Square::Square(const std::string& square_str) {
    // square_str is in the format of "a1", "e4", etc.
    if (square_str.length() != 2) {
        throw Exceptions::InvalidArgumentException("Invalid square string. Square string must be in the format of 'a1', 'e4', etc.");
    }
    int8_t file = (int8_t)(square_str[0] - 'a'); 
    int8_t rank = (int8_t)(square_str[1] - '1'); 
    index = rank * 8 + file;
}

Square& Square::operator=(const Square& other) {
    if (this == &other) {
        return *this; // handle self assignment
    }
    index = other.index;
    return *this;
}

Square& Square::operator=(const int8_t& new_index) {
    index = new_index;
    return *this;
}

void Square::set_square(int8_t file, int8_t rank) {
    index = rank * 8 + file;
}

void Square::set_square(int8_t new_index) {
    index = new_index;
}

bool Square::operator==(const std::string& other) const {
    // other is in the format of "a1", "e4", etc.
    if (other.length() != 2) {
        return false;
    }
    int8_t other_file = other[0] - 'a'; 
    int8_t other_rank = other[1] - '1'; 
    return file() == other_file && rank() == other_rank;
}

bool Square::operator==(const char *other) const {
    // other is in the format of "a1", "e4", etc.
    if (strlen(other) != 2) {
        return false;
    }
    int8_t other_file = (int8_t)(other[0] - 'a'); 
    int8_t other_rank = (int8_t)(other[1] - '1'); 
    return file() == other_file && rank() == other_rank;
}

Square::operator int() const { return index; }

Square Square::apply_offset(const int file_offset, const int rank_offset, bool inplace) {
        int8_t new_file = file() + file_offset;
        int8_t new_rank = rank() + rank_offset;
        if (new_file < 0 || new_file > 7 || new_rank < 0 || new_rank > 7) {
            if (inplace) {
                this->index = INT8_MAX; // set to invalid square if out of bounds
                return *this;
            }
            return Square(); // return invalid square if out of bounds
        }
        if (inplace) {
            this->set_square(new_file, new_rank);
            return *this;
        }
        else {
            return Square(new_file, new_rank);
        }
    }

std::string Square::to_string() const {
    // convert from index to string format "a1", "e4", etc.
    char file_char = (char)('a' + file()); 
    char rank_char = (char)('1' + rank()); 
    return std::string(1, file_char) + std::string(1, rank_char);
}