#include <bits/stdc++.h>
using namespace std;

/*
Disjoint Set Union (Union-Find)
- Union: O(α(n)) amortized
- Find: O(α(n)) amortized
- α(n) is the inverse Ackermann function (practically constant)
*/
class DSU {
private:
    vector<int> parent, rank, size_;
    int num_sets;

public:
    DSU(int n) : parent(n), rank(n, 0), size_(n, 1), num_sets(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false; // Already in same set
        
        // Union by rank
        if (rank[px] < rank[py]) {
            swap(px, py);
        }
        parent[py] = px;
        size_[px] += size_[py];
        
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
        
        num_sets--;
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return size_[find(x)];
    }

    int num_components() const {
        return num_sets;
    }
};
