#include "pch.h"
#include "dijkstra.h"
#include <queue>
#include <climits>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Custom hash function for Vector2Int if needed (for unordered_map keys)
struct Vector2IntHash {
    size_t operator()(const Vector2Int& v) const {
        return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
    }
};

Dijkstra::Dijkstra(Grid* g) : grid(g) {}

vector<Vector2Int> Dijkstra::findShortestPath(Vector2Int start, Vector2Int end) {
    // Priority queue will store pairs of (distance, position)
    using PQElement = pair<int, Vector2Int>;
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;

    // Distance map from Vector2Int to int
    unordered_map<Vector2Int, int, Vector2IntHash> dist;
    unordered_map<Vector2Int, Vector2Int, Vector2IntHash> prev;

    // Initialize distances with a large number
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            dist[{x, y}] = INT_MAX;
        }
    }

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto [currentDist, currentPos] = pq.top();
        pq.pop();

        if (currentPos == end) break;

        if (currentDist > dist[currentPos]) continue;  // Already found better path

        // Get neighbors from grid (assumed to return vector<Vector2Int>)
        vector<Vector2Int> neighbors = grid->getNeighbors(currentPos);

        for (auto& neighbor : neighbors) {
            // Assuming each move costs 1
            int newDist = currentDist + 1;

            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = currentPos;
                pq.push({ newDist, neighbor });
            }
        }
    }

    vector<Vector2Int> path;

    if (dist[end] == INT_MAX) {
        // No path found
        return path;
    }

    // Reconstruct path backward
    for (Vector2Int at = end; at != start; at = prev[at]) {
        path.push_back(at);
    }
    path.push_back(start);

    reverse(path.begin(), path.end());
    return path;
}
