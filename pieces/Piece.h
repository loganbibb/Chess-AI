#ifndef PIECE_H
#define PIECE_H

class Piece {
    piece_colors color = NOCOLOR;
    char rank = 0;
    char file = 0;
public:
    Piece() {color = NOCOLOR; type = NOPIECE; file = 0; rank = 0;}
    Piece(piece_colors _color, char _file, char _rank) {
        color = _color;
        file = _file;
        rank = _rank;
    }
    piece_colors get_color() {return color;}
};

#endif