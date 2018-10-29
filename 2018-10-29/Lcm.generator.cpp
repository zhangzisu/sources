#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define lnt __int128
#define MAXN 1000
const int max = 800;
int vi[1000], pr[1000], pnt = 0;
inline void shai() {
    for (int i = 2; i < MAXN; i++) {
        if (!vi[i]) pr[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pr[j] >= MAXN) break;
            vi[i * pr[j]] = 1;
            if (i % pr[j] == 0) break;
        }
    }
}
inline lnt gcd(lnt a, lnt b) {
    return b ? gcd(b, a % b) : a;
}
lnt f[MAXN], g[MAXN];
lnt calc(int x) {
    memset(f, 0, sizeof(f));
    f[x] = 1;
    for (int i = 1; i <= pnt; i++) {
        memcpy(g, f, sizeof(g));
        for (int j = 1; j <= x; j *= pr[i]) {
            for (int k = 0; k <= x - j; k++) {
                g[k] = std::max(g[k], f[k + j] * j);
            }
        }
        memcpy(f, g, sizeof(g));
    }
    return f[0];
}
void print(lnt x) {
    static int top[100];
    int t = 0;
    while (x) top[++t] = x % 10, x /= 10;
    for (int i = t; i; i--) putchar(top[i] ^ 48);
}
int main() {
    shai();
    freopen("Lcm.data", "w", stdout);
    for (int i = 0; i < max; i++) {
        print(calc(i));
        puts("");
    }
    print(calc(max));
    return 0;
}