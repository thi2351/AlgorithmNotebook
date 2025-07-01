#include <bits/stdc++.h>
using namespace std;

/*
Tonelli-Shanks Algorithm
- Solves x^2 ≡ n (mod p) for x
- p must be an odd prime
- Returns a solution x, or -1 if no solution exists
- Time: O(log^2 p)
*/
long long mod_pow(long long a, long long b, long long p) {
    long long res = 1;
    a %= p;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

long long tonelli_shanks(long long n, long long p) {
    if (mod_pow(n, (p - 1) / 2, p) != 1) return -1;
    if (p % 4 == 3) return mod_pow(n, (p + 1) / 4, p);
    long long q = p - 1, s = 0;
    while (q % 2 == 0) q /= 2, ++s;
    long long z = 2;
    while (mod_pow(z, (p - 1) / 2, p) != p - 1) ++z;
    long long c = mod_pow(z, q, p);
    long long r = mod_pow(n, (q + 1) / 2, p);
    long long t = mod_pow(n, q, p);
    long long m = s;
    while (t != 1) {
        long long i = 1, tmp = t * t % p;
        while (tmp != 1) tmp = tmp * tmp % p, ++i;
        long long b = mod_pow(c, 1LL << (m - i - 1), p);
        r = r * b % p;
        t = t * b % p * b % p;
        c = b * b % p;
        m = i;
    }
    return r;
}
