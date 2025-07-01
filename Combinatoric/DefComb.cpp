#include <bits/stdc++.h>
using namespace std;

/*
Factorial and Binomial Coefficient (nCr)
- Precompute factorials and inverses for fast nCr
- Time: O(n) preprocessing, O(1) query
*/
const int MOD = 1'000'000'007;
const int MAXN = 1'000'005;
long long fact[MAXN], invfact[MAXN];

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

void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN - 1] = modinv(fact[MAXN - 1], MOD);
    for (int i = MAXN - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}
