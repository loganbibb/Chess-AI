// std includes
#include <iostream>
// my files
// #include "Board.h"
#include "pieces/piece_colors.h"
#include "pieces/Pawn.h"

using namespace std;

int main() {
    Pawn p(WHITE, char(0), char(2));
    printf("Pawn color: %d\n", p.get_color());
    printf("success\n");
    return 0;
}