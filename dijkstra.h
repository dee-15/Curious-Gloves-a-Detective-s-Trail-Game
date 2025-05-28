#pragma once

#include <vector>
#include "Vector2Int.h"  // Define Vector2Int as mentioned pehle
#include "grid.h"

using namespace std;

class Dijkstra {
    Grid* grid; // Pointer to Grid representing the map

public:
    Dijkstra(Grid* g);

    // Find shortest path from start to end in 2D grid coordinates
    // Returns vector of Vector2Int positions forming the path
    vector<Vector2Int> findShortestPath(Vector2Int start, Vector2Int end);
};
