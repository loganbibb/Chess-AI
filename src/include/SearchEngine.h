#pragma once

#include "Position.h"

class SearchEngine {
    Position& position; // make reference so that we can modify the position in place
    float minimax(int depth, Colors player, float alpha, float beta);
    public:
        SearchEngine(Position& position) : position(position) {}
        Move search(int depth, Colors player);
};