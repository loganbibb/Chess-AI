// std includes
#include <iostream>
// my files
#include "include/Position.h"

using namespace std;

int main() {
    // Set up: White king on e1, white knight on e2 pinned by black rook on e8
    Position pos; 

    float eval = pos.get_eval();
    cout << "Evaluation of the position: " << eval << endl;
    return 0;
}