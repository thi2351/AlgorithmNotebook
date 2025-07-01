#include <bits/stdc++.h>
using namespace std;

/*
Lucas' Theorem for nCr mod prime
- Computes nCr mod p for large n, r and prime p
- Time: O(p^2 log n)
*/
long long modinv(long long a, long long p) {
    long long m0 = p, y = 0, x = 1;
    if (p == 1) return 0;
    while (a > 1) {
        long long q = a / p;
        long long t = p;
        p = a % p, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

long long nCr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) return 0;
    long long res = 1;
    while (n > 0 || r > 0) {
        long long ni = n % p, ri = r % p;
        if (ri > ni) return 0;
        // Compute niCrimodp
        long long num = 1, den = 1;
        for (long long i = 0; i < ri; i++) {
            num = num * (ni - i) % p;
            den = den * (i + 1) % p;
        }
        res = res * num % p * modinv(den, p) % p;
        n /= p;
        r /= p;
    }
    return res;
}
