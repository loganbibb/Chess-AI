#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Position.h"

class SearchEngine {
    Position& position; // make reference so that we can modify the position in place
    enum Player {WHITE, BLACK};
    float minimax(int depth, Player player, float& alpha, float& beta);
    public:
        SearchEngine(Position& position) : position(position) {}
        void link_position(Position& new_position) {position = new_position;};
        Move search(int depth, Player player);
};

#endif