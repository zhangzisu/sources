#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 1000000007
void printb(int x, int len) {
    for (int i = len; i; i--) putchar('0' ^ ((x >> (i - 1)) & 1));
    putchar(10);
}
inline int fuck(int x, int p) {
    register int ret = 1;
    while (p) {
        if (p & 1) ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
std::vector<int> V;
int gen(int len) {
    int ret = fuck(2, len);
    V.clear();
    for (int i = 2; i * i <= len; i++) {
        if (len % i) continue;
        V.push_back(i);
        if (i != len / i) V.push_back(len / i);
    }
    for (int i = 1; i < (1 << V.size()); i++) {
        int gcd = 0, lcm = 0;
        for (int j = 0; j < (int)V.size(); j++)
            if ((i >> j) & 1) {
                if (gcd) {
                    gcd = ::gcd(gcd, V[j]);
                    lcm = lcm / ::gcd(lcm, V[j]) * V[j];
                } else {
                    gcd = lcm = V[j];
                }
            }
        int way = fuck(2, gcd - 1);
        int rpt = fuck(2, len / lcm);
        ret += ((__builtin_popcount(i) & 1) ? -1LL : 1LL) * way * rpt % MOD;
        if (ret >= MOD) ret -= MOD;
        if (ret < 0) ret += MOD;
    }
    printf("GEN %3d = %5d\n", len, ret);
    return ret;
}
int n, ans = 0;
int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) ans += gen(i);
    printf("%d\n", ans);
    return 0;
}