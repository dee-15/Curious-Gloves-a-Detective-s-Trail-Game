#ifndef MINIMAX_H
#define MINIMAX_H

#include "Vector2Int.h"  // 2D position struct

// External variables representing current positions (2D coordinates)
extern Vector2Int thiefPosition;
extern Vector2Int detectivePosition;

// Minimax algorithm function
// depth: current search depth
// isDetective: true if detective's turn, false if thief's turn
// Returns: evaluation score of the state
int minimax(int depth, bool isDetective);

// Evaluation function to score current game state
// Returns: integer score based on detective and thief positions
int evaluate();

// Function to get best move for detective
// Returns: Vector2Int representing move direction (e.g. (-1,0), (0,1) etc.)
Vector2Int getBestMove();

#endif // MINIMAX_H
