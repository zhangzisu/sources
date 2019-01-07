#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 10007
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
char c = getchar();
int x = 0;
int main() {
    while (!isdigit(c)) c = getchar();
    for (; isdigit(c); c = getchar()) x = ((x << 1) + (x << 3) + (c ^ 48)) % MOD;
    return printf("%lld\n", (1LL * x * (x + 1) % MOD * (x + 2) % MOD * fuck(6, MOD - 2) % MOD + MOD) % MOD), 0;
}