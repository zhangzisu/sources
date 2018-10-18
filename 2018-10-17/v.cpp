#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 30
int n, k, init, cnt;
char buf[50];
typedef long long lnt;
struct HashMap {
    const static int MOD = 19260817;
    const static int SIZE = 5000010;
    int head[MOD], next[SIZE], tot;
    lnt key[SIZE];
    double val[SIZE];
    inline HashMap() {
        memset(head, 0, sizeof(head));
        tot = 0;
    }
    inline double* get(lnt k) {
        int p = k % MOD;
        for (int i = head[p]; i; i = next[i]) {
            if (key[i] == k) return val + i;
        }
        next[++tot] = head[p], key[tot] = k, head[p] = tot;
        return val + tot;
    }
} map;
inline int remove(int x, int p) {
    return (x >> (p + 1) << p) | (x & ((1 << p) - 1));
}
double dfs(int stat, int now) {
    int tmp = map.tot;
    double* res = map.get((lnt)now << 30 | stat);
    if (tmp == map.tot) return *res;
    if (now >= k - 1) {
        for (int i = 0; i < n - now; i++)
            *res += std::max(((stat >> i) & 1), ((stat >> (n - now - i - 1)) & 1));
    } else {
        for (int i = 0; i < n - now; i++)
            *res += std::max(dfs(remove(stat, i), now + 1) + ((stat >> i) & 1), dfs(remove(stat, n - now - i - 1), now + 1) + ((stat >> (n - now - i - 1)) & 1));
    }
    *res /= n - now;
    return *res;
}
int main() {
    scanf("%d%d%s", &n, &k, buf);
    for (int i = 0; i < n; i++) init |= (buf[i] == 'W') << i;
    if (k == 0) return puts("0"), 0;
    if (k == n) return printf("%d\n", __builtin_popcount(init)), 0;
    printf("%f\n", dfs(init, 0));
    fprintf(stderr, "%d\n", map.tot);
    return 0;
}