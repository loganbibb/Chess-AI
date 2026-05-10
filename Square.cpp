#include <string> 
#include <cstring>
#include "Square.h"

Square::Square(char file, char rank) {
    // file is 0-7, where 0 is a and 7 is h. rank is 0-7, where 0 is 1 and 7 is 8.
    index = rank * 8 + file;
}

Square::Square(char new_index) {
    index = new_index;
}

Square& Square::operator=(const Square& other) {
    if (this == &other) {
        return *this; // handle self assignment
    }
    index = other.index;
    return *this;
}

Square& Square::operator=(const char& new_index) {
    index = new_index;
    return *this;
}

void Square::set_square(char file, char rank) {
    index = rank * 8 + file;
}

void Square::set_square(char new_index) {
    index = new_index;
}

char Square::operator()() const {
    return index;
}

bool Square::operator==(const std::string& other) const {
    // other is in the format of "a1", "e4", etc.
    if (other.length() != 2) {
        return false;
    }
    char other_file = other[0] - 'a'; 
    char other_rank = other[1] - '1'; 
    return file() == other_file && rank() == other_rank;
}

bool Square::operator==(const char *other) const {
    // other is in the format of "a1", "e4", etc.
    if (strlen(other) != 2) {
        return false;
    }
    char other_file = other[0] - 'a'; 
    char other_rank = other[1] - '1'; 
    return file() == other_file && rank() == other_rank;
}

bool Square::operator==(const Square& other) const {
    return index == other.index;
}

Square::operator int() const { return index; }

std::string Square::to_string() const {
    // convert from index to string format "a1", "e4", etc.
    char file_char = 'a' + file(); 
    char rank_char = '1' + rank(); 
    return std::string(1, file_char) + std::string(1, rank_char);
}