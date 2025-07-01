#include <bits/stdc++.h>
using namespace std;

/*
Floyd-Warshall Algorithm
- Time: O(V^3)
- Space: O(V^2)
- Finds all-pairs shortest paths
- Works with negative edge weights (no negative cycles)
- Detects negative cycles
*/
class FloydWarshall {
private:
    vector<vector<int>> dist;
    vector<vector<int>> next;
    int n;
    static const int INF = 1e9;

public:
    FloydWarshall(int vertices) : n(vertices) {
        dist.resize(n, vector<int>(n, INF));
        next.resize(n, vector<int>(n, -1));
        
        // Initialize diagonal
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
    }

    void add_edge(int u, int v, int weight) {
        dist[u][v] = weight;
        next[u][v] = v;
    }

    // Compute all-pairs shortest paths
    // Returns true if no negative cycles, false otherwise
    bool compute() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && 
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        
        // Check for negative cycles
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                return false; // Negative cycle detected
            }
        }
        
        return true;
    }

    // Get shortest distance from u to v
    int get_distance(int u, int v) {
        return dist[u][v];
    }

    // Get shortest path from u to v
    vector<int> get_path(int u, int v) {
        vector<int> path;
        
        if (dist[u][v] == INF) {
            return path; // No path exists
        }
        
        int current = u;
        while (current != v) {
            path.push_back(current);
            current = next[current][v];
        }
        path.push_back(v);
        
        return path;
    }

    // Check if there's a negative cycle
    bool has_negative_cycle() {
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                return true;
            }
        }
        return false;
    }

    // Get the distance matrix
    vector<vector<int>> get_distance_matrix() {
        return dist;
    }

    // Get the next matrix for path reconstruction
    vector<vector<int>> get_next_matrix() {
        return next;
    }
};
