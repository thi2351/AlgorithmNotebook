#include <bits/stdc++.h>
using namespace std;

/*
Sparse Table
- Preprocessing: O(n log n)
- Range query: O(1)
- Supports min, max, gcd, lcm operations
*/
class SparseTable {
private:
    vector<vector<int>> st;
    vector<int> log_table;
    function<int(int, int)> op;
    int n;

public:
    SparseTable(const vector<int>& arr, function<int(int, int)> operation)
        : op(operation), n(arr.size()) {
        
        // Precompute logarithms
        log_table.resize(n + 1);
        log_table[1] = 0;
        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i / 2] + 1;
        }

        // Build sparse table
        int k = log_table[n] + 1;
        st.resize(n, vector<int>(k));
        
        for (int i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }
        
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query range [l, r] (0-based)
    int query(int l, int r) {
        int j = log_table[r - l + 1];
        return op(st[l][j], st[r - (1 << j) + 1][j]);
    }

    // Static methods for common operations
    static SparseTable min_table(const vector<int>& arr) {
        return SparseTable(arr, [](int a, int b) { return min(a, b); });
    }

    static SparseTable max_table(const vector<int>& arr) {
        return SparseTable(arr, [](int a, int b) { return max(a, b); });
    }

    static SparseTable gcd_table(const vector<int>& arr) {
        return SparseTable(arr, [](int a, int b) { return __gcd(a, b); });
    }
};
