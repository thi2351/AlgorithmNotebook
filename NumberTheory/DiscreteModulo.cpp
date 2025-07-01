#include <bits/stdc++.h>
using namespace std;

/*
Discrete Logarithm (Baby-step Giant-step)
- Solves a^x ≡ b (mod m) for x
- Time: O(sqrt(m) log m)
*/
long long discrete_log(long long a, long long b, long long m) {
    a %= m, b %= m;
    if (b == 1) return 0;
    long long n = sqrt(m) + 1;
    unordered_map<long long, long long> vals;
    long long an = 1;
    for (long long i = 0; i < n; ++i)
        an = an * a % m;
    long long cur = b;
    for (long long q = 0; q <= n; ++q) {
        vals[cur] = q;
        cur = cur * a % m;
    }
    cur = an;
    for (long long p = 1; p <= n; ++p) {
        if (vals.count(cur)) {
            return p * n - vals[cur];
        }
        cur = cur * an % m;
    }
    return -1;
}
