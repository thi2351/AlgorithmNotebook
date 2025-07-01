#include <bits/stdc++.h>
using namespace std;

/*
2D Fenwick Tree (Binary Indexed Tree)
- Point update: O(log n * log m)
- Range sum query: O(log n * log m)
- 1-based indexing
*/
class FenwickTree2D {
private:
    vector<vector<int>> tree;
    int n, m;

public:
    FenwickTree2D(int rows, int cols) : n(rows), m(cols), tree(rows + 1, vector<int>(cols + 1, 0)) {}

    FenwickTree2D(const vector<vector<int>>& matrix) : n(matrix.size()), m(matrix[0].size()), tree(n + 1, vector<int>(m + 1, 0)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                update(i + 1, j + 1, matrix[i][j]);
            }
        }
    }

    // Add val to position (x, y) (1-based)
    void update(int x, int y, int val) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                tree[i][j] += val;
            }
        }
    }

    // Get sum from (1,1) to (x, y) (1-based)
    int query(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // Get sum from (x1, y1) to (x2, y2) (1-based)
    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }

    // Get value at position (x, y) (1-based)
    int get(int x, int y) {
        return query(x, y) - query(x, y - 1) - query(x - 1, y) + query(x - 1, y - 1);
    }

    // Set value at position (x, y) (1-based)
    void set(int x, int y, int val) {
        int current = get(x, y);
        update(x, y, val - current);
    }
};
