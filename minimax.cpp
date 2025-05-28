#include "pch.h"
#include "Minimax.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Current positions of thief and detective (2D)
Vector2Int thiefPosition(0, 0);
Vector2Int detectivePosition(0, 0);

// Directions (up, down, left, right)
const vector<Vector2Int> directions = {
    Vector2Int(0,1), Vector2Int(0,-1), Vector2Int(1,0), Vector2Int(-1,0)
};

// Example grid size - change as per your grid
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;

// Dummy function to check if position is valid and walkable in the grid
bool isValidPosition(const Vector2Int& pos) {
    return (pos.x >= 0 && pos.x < GRID_WIDTH && pos.y >= 0 && pos.y < GRID_HEIGHT);
    // You can add grid obstacle check here, e.g., return grid[pos.x][pos.y] == walkable;
}

// Manhattan distance evaluation (smaller is better for detective)
int evaluate() {
    return abs(thiefPosition.x - detectivePosition.x) + abs(thiefPosition.y - detectivePosition.y);
}

// Recursive minimax function
int minimax(int depth, bool isDetective) {
    if (depth == 0 || thiefPosition == detectivePosition) {
        return -evaluate();  // negative so detective tries to minimize distance
    }

    if (isDetective) {
        int best = -9999;
        for (const auto& dir : directions) {
            Vector2Int newPos = detectivePosition + dir;
            if (!isValidPosition(newPos)) continue;

            detectivePosition = newPos;
            int val = minimax(depth - 1, false);
            best = max(best, val);
            detectivePosition = detectivePosition + Vector2Int(-dir.x, -dir.y); // backtrack
        }
        return best;
    }
    else {
        int best = 9999;
        for (const auto& dir : directions) {
            Vector2Int newPos = thiefPosition + dir;
            if (!isValidPosition(newPos)) continue;

            thiefPosition = newPos;
            int val = minimax(depth - 1, true);
            best = min(best, val);
            thiefPosition = thiefPosition + Vector2Int(-dir.x, -dir.y); // backtrack
        }
        return best;
    }
}

// Function to get the best move for detective
Vector2Int getBestMove() {
    int bestVal = -9999;
    Vector2Int bestMove(0, 0);

    for (const auto& dir : directions) {
        Vector2Int newPos = detectivePosition + dir;
        if (!isValidPosition(newPos)) continue;

        detectivePosition = newPos;
        int moveVal = minimax(3, false);
        detectivePosition = detectivePosition + Vector2Int(-dir.x, -dir.y);

        if (moveVal > bestVal) {
            bestVal = moveVal;
            bestMove = dir;
        }
    }

    return bestMove;
}
