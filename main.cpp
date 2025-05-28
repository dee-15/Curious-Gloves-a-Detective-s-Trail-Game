#include "pch.h"
#include <iostream>
#include "grid.h"
#include "dijkstra.h"
#include "minimax.h"

using namespace std;

// No local thiefPosition or detectivePosition declared here; using global ones from minimax.cpp

int main() {
    Grid grid;                      // Create the grid object
    Dijkstra dijkstra(&grid);      // Initialize Dijkstra with reference to the grid

    // Initialize global positions (from minimax.cpp)
    thiefPosition = 0;             // Thief starts at position 0
    detectivePosition = 9;         // Detective starts at position 9

    int step = 0;                  // Counter to track steps taken
    const int MAX_STEPS = 100;     // Safety limit to prevent infinite loops

    // Game loop: runs until thief is caught or max steps reached
    while (thiefPosition != detectivePosition && step++ < MAX_STEPS) {
        // Display current positions
        cout << "Step " << step << " - Thief: " << thiefPosition
            << " | Detective: " << detectivePosition << endl;

        // Use Dijkstra to find shortest path from thief to detective
        auto path = dijkstra.findShortestPath(thiefPosition, detectivePosition);

        // If no valid path (e.g., disconnected grid), exit loop
        if (path.size() < 2) {
            cout << "Thief is stuck or unreachable!\n";
            break;
        }

        // Move thief to next position along shortest path
        thiefPosition = path[1].first;

        // Use Minimax to decide the best move for the detective
        int bestMove = getBestMove();
        detectivePosition += bestMove;

        // Ensure both thief and detective remain within grid bounds (0 to 9)
        if (detectivePosition < 0) detectivePosition = 0;
        if (detectivePosition > 9) detectivePosition = 9;
        if (thiefPosition < 0) thiefPosition = 0;
        if (thiefPosition > 9) thiefPosition = 9;
    }

    // Final outcome after exiting loop
    if (thiefPosition == detectivePosition) {
        cout << "Detective caught the thief!" << endl;
    }
    else {
        cout << "Maximum steps reached. Game ended." << endl;
    }

    return 0;
}
