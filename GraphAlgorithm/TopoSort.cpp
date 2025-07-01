#include <bits/stdc++.h>
using namespace std;

/*
Topological Sort
- DFS: O(V + E)
- Kahn's: O(V + E)
- Works only on Directed Acyclic Graphs (DAG)
*/

class TopologicalSort {
private:
    vector<vector<int>> adj;
    int n;

public:
    TopologicalSort(int vertices) : n(vertices), adj(vertices) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    // DFS-based topological sort
    vector<int> dfs_toposort() {
        vector<int> order;
        vector<bool> visited(n, false);
        vector<bool> rec_stack(n, false);
        
        function<bool(int)> dfs = [&](int u) {
            visited[u] = true;
            rec_stack[u] = true;
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    if (dfs(v)) return true; // Cycle detected
                } else if (rec_stack[v]) {
                    return true; // Back edge - cycle detected
                }
            }
            
            rec_stack[u] = false;
            order.push_back(u);
            return false;
        };
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i)) {
                    return {}; // Cycle detected, no topological order
                }
            }
        }
        
        reverse(order.begin(), order.end());
        return order;
    }

    // Kahn's algorithm (BFS-based)
    vector<int> kahns_toposort() {
        vector<int> in_degree(n, 0);
        
        // Calculate in-degrees
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                in_degree[v]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> order;
        int visited_count = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            visited_count++;
            
            for (int v : adj[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        if (visited_count != n) {
            return {}; // Cycle detected, no topological order
        }
        
        return order;
    }

    // Check if graph is a DAG
    bool is_dag() {
        return !dfs_toposort().empty();
    }

    // Get all topological orders (if multiple exist)
    vector<vector<int>> all_toposorts() {
        vector<vector<int>> all_orders;
        vector<bool> visited(n, false);
        vector<int> in_degree(n, 0);
        
        // Calculate in-degrees
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                in_degree[v]++;
            }
        }
        
        function<void(vector<int>&, vector<bool>&, vector<int>&)> backtrack = 
            [&](vector<int>& order, vector<bool>& visited, vector<int>& in_degree) {
                if (order.size() == n) {
                    all_orders.push_back(order);
                    return;
                }
                
                for (int i = 0; i < n; i++) {
                    if (!visited[i] && in_degree[i] == 0) {
                        visited[i] = true;
                        order.push_back(i);
                        
                        // Update in-degrees
                        for (int v : adj[i]) {
                            in_degree[v]--;
                        }
                        
                        backtrack(order, visited, in_degree);
                        
                        // Restore in-degrees
                        for (int v : adj[i]) {
                            in_degree[v]++;
                        }
                        
                        order.pop_back();
                        visited[i] = false;
                    }
                }
            };
        
        vector<int> order;
        backtrack(order, visited, in_degree);
        return all_orders;
    }
};
