#include <bits/stdc++.h>
using namespace std;

/*
Minimum Spanning Tree Algorithms
- Kruskal: O(E log E) with Union-Find
- Prim: O(E log V) with binary heap
*/

// Kruskal's Algorithm
class KruskalMST {
private:
    struct Edge {
        int u, v, weight;
        Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };
    
    vector<Edge> edges;
    int n;

public:
    KruskalMST(int vertices) : n(vertices) {}

    void add_edge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }

    // Returns MST edges and total weight
    pair<vector<Edge>, int> find_mst() {
        sort(edges.begin(), edges.end());
        
        vector<Edge> mst_edges;
        int total_weight = 0;
        
        // DSU for cycle detection
        vector<int> parent(n), rank(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        // Define find after parent is initialized
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unite = [&](int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return false;
            
            if (rank[px] < rank[py]) swap(px, py);
            parent[py] = px;
            if (rank[px] == rank[py]) rank[px]++;
            return true;
        };
        
        for (const Edge& edge : edges) {
            if (unite(edge.u, edge.v)) {
                mst_edges.push_back(edge);
                total_weight += edge.weight;
            }
        }
        
        return {mst_edges, total_weight};
    }
};

// Prim's Algorithm
class PrimMST {
private:
    vector<vector<pair<int, int>>> adj; // {to, weight}
    int n;

public:
    PrimMST(int vertices) : n(vertices), adj(vertices) {}

    void add_edge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Undirected graph
    }

    // Returns MST edges and total weight
    pair<vector<pair<int, int>>, int> find_mst(int start = 0) {
        vector<bool> visited(n, false);
        vector<pair<int, int>> mst_edges;
        int total_weight = 0;
        
        priority_queue<pair<int, pair<int, int>>, 
                      vector<pair<int, pair<int, int>>>, 
                      greater<pair<int, pair<int, int>>>> pq;
        
        pq.push({0, {start, start}});
        
        while (!pq.empty()) {
            int weight = pq.top().first;
            int u = pq.top().second.first;
            int parent = pq.top().second.second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            if (u != parent) {
                mst_edges.push_back({parent, u});
                total_weight += weight;
            }
            
            for (auto [v, w] : adj[u]) {
                if (!visited[v]) {
                    pq.push({w, {v, u}});
                }
            }
        }
        
        return {mst_edges, total_weight};
    }
};
