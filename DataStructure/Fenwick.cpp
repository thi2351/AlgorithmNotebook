#include <bits/stdc++.h>
using namespace std;

/*
Fenwick Tree (Binary Indexed Tree)
- Point update: O(logn)
- Range sum query: O(logn)
- 1-based indexing
*/
class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    FenwickTree(const vector<int>& arr) : n(arr.size()), tree(arr.size() + 1, 0) {
        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]);
        }
    }

    // Add val to position pos (1-based)
    void update(int pos, int val) {
        while (pos <= n) {
            tree[pos] += val;
            pos += pos & -pos; // Add least significant bit
        }
    }

    // Get sum from 1 to pos (1-based)
    int query(int pos) {
        int sum = 0;
        while (pos > 0) {
            sum += tree[pos];
            pos -= pos & -pos; // Remove least significant bit
        }
        return sum;
    }

    // Get sum from l to r (1-based)
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Get value at position pos (1-based)
    int get(int pos) {
        return query(pos) - query(pos - 1);
    }

    // Set value at position pos (1-based)
    void set(int pos, int val) {
        int current = get(pos);
        update(pos, val - current);
    }
};
