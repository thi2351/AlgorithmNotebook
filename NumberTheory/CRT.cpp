#include <bits/stdc++.h>
using namespace std;

/*
Chinese Remainder Theorem (CRT)
- Solves x ≡ a_i (mod m_i) for all i
- Returns {x, M} where x is the solution modulo M = lcm(m_i)
- Time: O(n log M)
*/
pair<long long, long long> crt(const vector<long long>& a, const vector<long long>& m) {
    long long x = 0, M = 1;
    for (int i = 0; i < a.size(); ++i) {
        long long a_i = a[i] % m[i];
        long long m_i = m[i];
        long long p, q;
        long long g = std::gcd(M, m_i);
        if ((a_i - x) % g != 0) return {0, -1}; // No solution
        long long inv = modinv(M / g, m_i / g);
        x += M * ((a_i - x) / g * inv % (m_i / g));
        M *= m_i / g;
        x = (x % M + M) % M;
    }
    return {x, M};
}

// Helper: modular inverse
long long modinv(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}
