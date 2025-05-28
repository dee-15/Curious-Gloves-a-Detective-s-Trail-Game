#pragma once
#include <vector>

class Grid {
public:
    int width;
    int height;
    std::vector<std::vector<bool>> walkable;  // true means tile is walkable, false means obstacle

    // Constructor to initialize grid with width and height
    Grid(int w, int h);

    // Check if a position is inside grid boundaries
    bool isInside(int x, int y) const;

    // Check if a position is walkable (not obstacle and inside grid)
    bool isWalkable(int x, int y) const;
};
