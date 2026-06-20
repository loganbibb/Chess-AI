// std includes
#include <iostream>
// my files
#include "include/Position.h"

using namespace std;

int main() {
    Position pos;
    auto moves = pos.generate_moves();
    pos.show();
}