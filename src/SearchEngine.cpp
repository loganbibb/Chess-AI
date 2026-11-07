#include <cmath>
#include <limits>

#include "SearchEngine.h"

Move SearchEngine::search(int depth, Player player) {
    float alpha = -std::numeric_limits<float>::infinity();
    float beta = std::numeric_limits<float>::infinity();
    Move best_move;
    Unmove unmove; 

    // generate all legal moves and call minimax on each
    std::vector<Move> moves = position.generate_legal_moves();

    // first, check for terminal position 
    if (moves.empty()) {
        return best_move; // no legal moves, so return empty move
    }
    for (const auto& move : moves) {
        position.make_move(move, unmove);
        if (player == WHITE) {
            float eval = minimax(depth - 1, BLACK, alpha, beta);
            position.unmake_move(move, unmove);
            if (eval > alpha) {
                alpha = eval;
                best_move = move; 
            }
        } else {
            float eval = minimax(depth - 1, WHITE, alpha, beta);
            position.unmake_move(move, unmove);
            if (eval < beta) {
                beta = eval;
                best_move = move;
            }
        }
        // alpha-beta pruning
        if (beta <= alpha) {
            break; // prune remaining moves
        }
    }
    return best_move;
}

float SearchEngine::minimax(int depth, Player player, float& alpha, float& beta) {
    float eval; 
    if (depth == 0) {
        return position.get_eval();
    }
    Move best_move;
    Unmove unmove;

    // generate all legal moves and call minimax on each
    std::vector<Move> moves = position.generate_legal_moves();

    // first, check for terminal position 
    if (moves.empty()) {
        eval = position.eval_terminal_position();
        return eval; // no legal moves, so return empty move
    }
    for (const auto& move : moves) {
        position.make_move(move, unmove);
        if (player == WHITE) {
            eval = minimax(depth - 1, BLACK, alpha, beta);
            position.unmake_move(move, unmove);
            if (eval > alpha) {
                alpha = eval;
                best_move = move; 
            }
        } else {
            eval = minimax(depth - 1, WHITE, alpha, beta);
            position.unmake_move(move, unmove);
            if (eval < beta) {
                beta = eval;
                best_move = move;
            }
        }
        // alpha-beta pruning
        if (beta <= alpha) {
            break; // prune remaining moves
        }
    }
    return eval;
}