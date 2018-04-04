#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 400010
#define MOD 1000000007
#define _ long long
_ fuck(_ x, _ p) {
    _ y = 1;
    while (p) {
        if (p & 1) y = x * y % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return y;
}
_ frc[MAXN], inv[MAXN];
inline _ C(int n, int m) { return frc[n] * inv[m] % MOD * inv[n - m] % MOD; }

int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = inv[i] * i % MOD;
    //
    return 0;
}