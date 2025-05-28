#include "pch.h"
#include "grid.h"
#include <vector>

using namespace std;

// Constructor with width and height initialization
Grid::Grid(int w, int h) : width(w), height(h) {
    // Initialize the grid with all walkable = true by default
    walkableGrid.resize(height, vector<bool>(width, true));
}

// Function to check if a given position is inside the grid bounds
bool Grid::isInsideGrid(Vector2Int pos) {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}

// Function to set whether a cell is walkable or not
void Grid::setWalkable(Vector2Int pos, bool walkable) {
    if (isInsideGrid(pos)) {
        walkableGrid[pos.y][pos.x] = walkable;
    }
}

// Get neighbors (up, down, left, right) for a given 2D position
vector<Vector2Int> Grid::getNeighbors(Vector2Int pos) {
    vector<Vector2Int> neighbors;

    // Define 4 directions (up, down, left, right)
    vector<Vector2Int> directions = {
        Vector2Int(0, -1), // up
        Vector2Int(0, 1),  // down
        Vector2Int(-1, 0), // left
        Vector2Int(1, 0)   // right
    };

    for (const auto& dir : directions) {
        Vector2Int neighborPos(pos.x + dir.x, pos.y + dir.y);

        // Check boundaries and walkability
        if (isInsideGrid(neighborPos) && walkableGrid[neighborPos.y][neighborPos.x]) {
            neighbors.push_back(neighborPos);
        }
    }

    return neighbors;
}
