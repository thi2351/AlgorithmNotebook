#include <bits/stdc++.h>
using namespace std;

/*
Bellman-Ford Algorithm
- Time: O(VE)
- Space: O(V)
- Finds shortest paths from single source
- Works with negative edge weights
- Detects negative cycles
*/
class BellmanFord {
private:
    struct Edge {
        int from, to, weight;
        Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
    };
    
    vector<Edge> edges;
    int n;

public:
    BellmanFord(int vertices) : n(vertices) {}

    void add_edge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }

    // Returns shortest distances from source to all vertices
    // Returns empty vector if negative cycle is detected
    vector<int> shortest_paths(int source) {
        vector<int> dist(n, INT_MAX);
        dist[source] = 0;
        
        // Relax all edges V-1 times
        for (int i = 0; i < n - 1; i++) {
            for (const Edge& edge : edges) {
                if (dist[edge.from] != INT_MAX && 
                    dist[edge.from] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                }
            }
        }
        
        // Check for negative cycles
        for (const Edge& edge : edges) {
            if (dist[edge.from] != INT_MAX && 
                dist[edge.from] + edge.weight < dist[edge.to]) {
                return {}; // Negative cycle detected
            }
        }
        
        return dist;
    }

    // Returns shortest path from source to target
    // Returns {INT_MAX, {}} if no path exists or negative cycle detected
    pair<int, vector<int>> shortest_path(int source, int target) {
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        dist[source] = 0;
        
        // Relax all edges V-1 times
        for (int i = 0; i < n - 1; i++) {
            for (const Edge& edge : edges) {
                if (dist[edge.from] != INT_MAX && 
                    dist[edge.from] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                    parent[edge.to] = edge.from;
                }
            }
        }
        
        // Check for negative cycles
        for (const Edge& edge : edges) {
            if (dist[edge.from] != INT_MAX && 
                dist[edge.from] + edge.weight < dist[edge.to]) {
                return {INT_MAX, {}}; // Negative cycle detected
            }
        }
        
        // Reconstruct path
        vector<int> path;
        if (dist[target] == INT_MAX) {
            return {INT_MAX, path};
        }
        
        for (int u = target; u != -1; u = parent[u]) {
            path.push_back(u);
        }
        reverse(path.begin(), path.end());
        
        return {dist[target], path};
    }

    // Detect negative cycles in the graph
    bool has_negative_cycle() {
        vector<int> dist(n, 0);
        
        // Run V iterations
        for (int i = 0; i < n; i++) {
            bool relaxed = false;
            for (const Edge& edge : edges) {
                if (dist[edge.from] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                    relaxed = true;
                }
            }
            if (!relaxed) break;
        }
        
        // Check if any edge can still be relaxed
        for (const Edge& edge : edges) {
            if (dist[edge.from] + edge.weight < dist[edge.to]) {
                return true; // Negative cycle found
            }
        }
        
        return false;
    }
};
