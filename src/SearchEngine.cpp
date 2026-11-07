#include <cmath>
#include <limits>

#include "error_types.h"
#include "evaluation.h"
#include "SearchEngine.h"

Move SearchEngine::search(int depth, Colors player) {
    if (player == Colors::NOCOLOR) {
        throw Exceptions::InvalidColorException("Invalid player color. Player must be either WHITE or BLACK.");
    }
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
        if (player == Colors::WHITE) {
            float eval = minimax(depth - 1, Colors::BLACK, alpha, beta);
            position.unmake_move(move, unmove);
            if (eval > alpha) {
                alpha = eval;
                best_move = move; 
            }
        } else {
            float eval = minimax(depth - 1, Colors::WHITE, alpha, beta);
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

float SearchEngine::minimax(int depth, Colors player, float& alpha, float& beta) {
    float eval; 
    Move best_move;
    Unmove unmove;

    // generate all legal moves and call minimax on each
    std::vector<Move> moves = position.generate_legal_moves();

    // first, check for terminal position 
    if (moves.empty()) {
        eval = position.eval_terminal_position();
        return eval; // no legal moves, so return empty move
    }

    if (depth == 0) {
        // if in check, extend search depth by 1 to look for checkmate / stalemate
        if (position.is_in_check(position.find_king(player), player)) {
            depth = 1; 
        } 
        else {
            return position.get_eval();
        }
    }

    for (const auto& move : moves) {
        position.make_move(move, unmove);
        if (player == Colors::WHITE) {
            eval = minimax(depth - 1, Colors::BLACK, alpha, beta);
            position.unmake_move(move, unmove);
            if (eval > alpha) {
                alpha = eval;
                best_move = move; 
            }
        } else {
            eval = minimax(depth - 1, Colors::WHITE, alpha, beta);
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