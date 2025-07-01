#include <bits/stdc++.h>
using namespace std;

/*
Dijkstra's Algorithm
- Time: O((V + E) log V) with binary heap
- Space: O(V)
- Finds shortest paths from single source
- Works with non-negative edge weights
*/
class Dijkstra {
private:
    vector<vector<pair<int, int>>> adj; // {to, weight}
    int n;

public:
    Dijkstra(int vertices) : n(vertices), adj(vertices) {}

    void add_edge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }

    // Returns shortest distances from source to all vertices
    vector<int> shortest_paths(int source) {
        vector<int> dist(n, INT_MAX);
        dist[source] = 0;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue; // Already processed
            
            for (auto [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }

    // Returns shortest path from source to target
    pair<int, vector<int>> shortest_path(int source, int target) {
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        dist[source] = 0;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (u == target) break;
            if (d > dist[u]) continue;
            
            for (auto [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
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
};
