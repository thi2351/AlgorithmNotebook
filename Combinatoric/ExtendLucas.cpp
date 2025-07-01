#include <bits/stdc++.h>
using namespace std;

/*
Extended Lucas' Theorem for nCr mod prime powers
- Computes nCr mod p^k for large n, r and prime p
- Time: O(p^2 log n)
*/
long long power(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long modinv(long long a, long long mod) {
    long long m0 = mod, y = 0, x = 1;
    if (mod == 1) return 0;
    while (a > 1) {
        long long q = a / mod;
        long long t = mod;
        mod = a % mod, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Helper for nCr mod p^k
long long nCr_mod_pk(long long n, long long r, long long p, long long pk) {
    if (r < 0 || r > n) return 0;
    long long res = 1;
    while (n > 0 || r > 0) {
        long long ni = n % p, ri = r % p;
        if (ri > ni) return 0;
        // Compute niCrimodpk
        long long num = 1, den = 1;
        for (long long i = 0; i < ri; i++) {
            num = num * (ni - i) % pk;
            den = den * (i + 1) % pk;
        }
        res = res * num % pk * modinv(den, pk) % pk;
        n /= p;
        r /= p;
    }
    return res;
}

// Extended Lucas
long long extended_lucas(long long n, long long r, long long p, long long k) {
    long long pk = 1;
    for (int i = 0; i < k; i++) pk *= p;
    return nCr_mod_pk(n, r, p, pk);
}
