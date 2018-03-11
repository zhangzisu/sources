#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define MOD 1000000007
#define MAXN 200010
int head[MAXN], to[MAXN], next[MAXN], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int size[MAXN], n, m, cur;
void dd(int x, int deep) {
    size[deep]++;
    m = std::max(m, deep);
    for (int i = head[x]; ~i; i = next[i]) dd(to[i], deep + 1);
}
struct state {
    long long v0, v1, v2;
    inline state(long long v0 = 0, long long v1 = 0, long long v2 = 0)
        : v0(v0), v1(v1), v2(v2) {}
    inline friend state operator|(const state &a, const state &b) {
        state ret;
        ret.v0 = a.v0 * b.v0 % MOD;
        ret.v1 = (a.v0 * b.v1 % MOD + a.v1 * b.v0 % MOD) % MOD;
        ret.v2 = (a.v0 * b.v2 % MOD + a.v1 * b.v1 % MOD + a.v1 * b.v2 % MOD +
                  a.v2 * b.v0 % MOD + a.v2 * b.v1 % MOD + a.v2 * b.v2 % MOD) %
                 MOD;
        return ret;
    }
};
inline long long fpow(long long x, int p) {
    register long long ret = 1;
    while (p) {
        if (p & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
long long ans = 0, hf = fpow(2, MOD - 2), dl;
int pos[MAXN], ppp;
void g(int x) {
    pos[++ppp] = x;
    for (int i = head[x]; ~i; i = next[i]) g(to[i]);
}
std::vector<state> f[MAXN];
int p[MAXN], vnt;
inline int Merge(int x, int y) {
    if (f[x].size() < f[y].size()) std::swap(x, y);
    const int X = f[x].size(), Y = f[y].size();
    for (unsigned i = 0; i < f[y].size(); i++) {
        f[x][X - i - 1] = f[x][X - i - 1] | f[y][Y - i - 1];
    }
    return x;
}
int main() {
    std::cin >> n;
    dl = fpow(2, n + 1);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        int p;
        std::cin >> p;
        $(p, i);
    }
    g(0);
    for (register int _ = ppp; _; _--) {
        register int x = pos[_], y = 0;
        if (!~head[x]) {
            p[x] = vnt++;
            f[p[x]].push_back(state(hf, hf, 0));
        } else {
            p[x] = p[to[head[x]]];
            for (int i = next[head[x]]; ~i; i = next[i]) {
                y = std::max(y,
                             (int)std::min(f[p[x]].size(), f[p[to[i]]].size()));
                p[x] = Merge(p[x], p[to[i]]);
            }
            f[p[x]].push_back(state(hf, hf, 0));
        }
        const int size = f[p[x]].size() - 1;
        for (int i = 1; i <= y; i++)
            f[p[x]][size - i].v0 += f[p[x]][size - i].v2,
                f[p[x]][size - i].v2 = 0;
    }
    for (unsigned i = 0; i < f[p[0]].size(); i++) {
        (ans += f[p[0]][i].v1 * dl % MOD) %= MOD;
    }
    std::cout << ans << std::endl;
}