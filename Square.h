#include <string> 
#include <cstring>

class Square{
    /*
    Square class represents a square on the chess board. It is essentially a
    wrapper for a char from 0 to 63, where 0 represents a1 and 63 represents h8. 
    Extra function added for operator overload for string comparison, so that we can easily convert between file/rank and square index.
    This class can be used to easily convert between file/rank and square index.
    */
    char index = 0; // 0-63, where 0 is a1 and 63 is h8

    public: 

    Square(char file, char rank);
    Square(char new_index);
    Square& operator=(const Square& other);
    Square& operator=(const char& new_index);
    void set_square(char file, char rank);
    void set_square(char new_index);
    inline char file();
    inline char rank();
    char operator()();
    bool operator==(const std::string& other);
    bool operator==(const char *other);
    bool operator==(const Square& other);
    std::string to_string();

};