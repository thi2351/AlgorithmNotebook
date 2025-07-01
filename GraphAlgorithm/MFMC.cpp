#include <bits/stdc++.h>
using namespace std;

/*
Min-Cost Max-Flow (MCMF) Algorithm
- Time: O(F * (V + E) * log V) with Dijkstra's potential
- Finds the maximum flow with the minimum cost in a flow network
*/
struct Edge {
    int to, rev;
    int cap, flow;
    int cost;
    Edge(int to, int rev, int cap, int cost) : to(to), rev(rev), cap(cap), flow(0), cost(cost) {}
};

class MinCostMaxFlow {
public:
    int n;
    vector<vector<Edge>> g;
    vector<int> dist, parent, parent_edge;
    vector<int> potential;

    MinCostMaxFlow(int n) : n(n), g(n) {}

    void add_edge(int u, int v, int cap, int cost) {
        g[u].emplace_back(v, g[v].size(), cap, cost);
        g[v].emplace_back(u, g[u].size() - 1, 0, -cost);
    }

    pair<int, int> flow(int s, int t, int maxf = INT_MAX) {
        int flow = 0, cost = 0;
        potential.assign(n, 0);
        while (flow < maxf) {
            dist.assign(n, INT_MAX);
            parent.assign(n, -1);
            parent_edge.assign(n, -1);
            dist[s] = 0;
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.emplace(0, s);
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d != dist[u]) continue;
                for (int i = 0; i < g[u].size(); ++i) {
                    Edge &e = g[u][i];
                    if (e.cap > e.flow) {
                        int v = e.to;
                        int nd = dist[u] + e.cost + potential[u] - potential[v];
                        if (dist[v] > nd) {
                            dist[v] = nd;
                            parent[v] = u;
                            parent_edge[v] = i;
                            pq.emplace(dist[v], v);
                        }
                    }
                }
            }
            if (dist[t] == INT_MAX) break;
            for (int i = 0; i < n; ++i) if (dist[i] < INT_MAX) potential[i] += dist[i];
            int addf = maxf - flow;
            int v = t;
            while (v != s) {
                int u = parent[v], i = parent_edge[v];
                addf = min(addf, g[u][i].cap - g[u][i].flow);
                v = u;
            }
            v = t;
            while (v != s) {
                int u = parent[v], i = parent_edge[v];
                g[u][i].flow += addf;
                g[v][g[u][i].rev].flow -= addf;
                v = u;
            }
            flow += addf;
            cost += addf * potential[t];
        }
        return {flow, cost};
    }
};
