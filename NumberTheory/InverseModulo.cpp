#include <bits/stdc++.h>
using namespace std;

/*
Modular Inverse (Extended Euclidean Algorithm)
- Finds x such that a*x ≡ 1 (mod m)
- Time: O(log m)
*/
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
