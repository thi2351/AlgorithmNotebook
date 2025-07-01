#include <bits/stdc++.h>
using namespace std;

/*
Recursive Binomial Coefficient (nCr) and Pascal's Triangle
- nCr: O(n*r) with memoization
- Pascal's triangle: O(n^2)
*/

// Recursive nCr with memoization
map<pair<int, int>, long long> nCr_memo;
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    auto key = make_pair(n, r);
    if (nCr_memo.count(key)) return nCr_memo[key];
    return nCr_memo[key] = nCr(n - 1, r - 1) + nCr(n - 1, r);
}

// Pascal's triangle
vector<vector<long long>> pascal_triangle(int n) {
    vector<vector<long long>> pt(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        pt[i][0] = pt[i][i] = 1;
        for (int j = 1; j < i; j++) {
            pt[i][j] = pt[i - 1][j - 1] + pt[i - 1][j];
        }
    }
    return pt;
}
