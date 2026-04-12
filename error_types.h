#include "string"

namespace Exceptions {
    class Exception {
    public: 
        int line {0};
        std::string msg;
        Exception(std::string message = "", int line_number = -1) : msg(message), line(line_number) {}
        Exception(const char* message, int line_number = -1) : msg(message), line(line_number) {}
        virtual std::string& what() = 0; // pure virtual function
    };

    class InvalidSquareException : public Exception {
    public:
        InvalidSquareException(const std::string& message = "Invalid square string. Square strings must be in the format of 'a1', 'e4', etc.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };

    class InvalidMoveException : public Exception {
    public:
        InvalidMoveException(const std::string& message = "Invalid move. Move does not meet the required conditions for a legal chess move.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };

    class InvalidPositionException : public Exception {
    public:
        InvalidPositionException(const std::string& message = "Invalid position. Position must be legal according to chess rules.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };

    class IndexError : public Exception {
    public:
        IndexError(const std::string& message = "Index out of bounds. Index must be between 0 and 63.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };

    class InvalidPieceException : public Exception {
    public:
        InvalidPieceException(const std::string& message = "Invalid piece. Piece must be one of the defined pieces in the Pieces enum.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };

    class InvalidColorException : public Exception {
    public:
        InvalidColorException(const std::string& message = "Invalid color. Color must be either WHITE or BLACK.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };

    class InvalidArgumentException : public Exception {
    public:
        InvalidArgumentException(const std::string& message = "Invalid argument. Argument does not meet the required conditions.", int line_number = -1)
            : Exception(message, line_number) {}
        std::string& what() override {
            return msg;
        }
    };
}