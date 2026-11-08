#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Position.h"

class SearchEngine {
    Position& position; // make reference so that we can modify the position in place
    float minimax(int depth, Colors player, float alpha, float beta);
    public:
        SearchEngine(Position& position) : position(position) {}
        void link_position(Position& new_position) {position = new_position;};
        Move search(int depth, Colors player);
};

#endif