#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
int _0;
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2, _5[64];
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline int $() {
    register int x = 0, f = 0;
    register char ch = gc();
    for (; !isdigit(ch); ch = gc()) f ^= ch == 45;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
inline void $(int x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(long long x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(const char *s) {
    for (; *s; s++) pc(*s);
}
#define MAXN 100010
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int id[MAXN], fa[MAXN], f[MAXN], g[MAXN], dfsclk;
void dfs(int x) {
    id[++dfsclk] = x;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        dfs(to[i]);
    }
}
inline void dp(int k) {
    for (int i = n, x; i >= 1; i--) {
        x = id[i];
        int max1 = 0, max2 = 0;
        f[x] = g[x] = 0;
        for (int i = head[x]; ~i; i = next[i]) {
            if (to[i] == fa[x]) continue;
            f[x] += f[to[i]];
            if (g[to[i]] >= max1) {
                max2 = max1, max1 = g[to[i]];
            } else if (g[to[i]] > max2) {
                max2 = g[to[i]];
            }
        }
        if (max1 + max2 + 1 >= k) {
            f[x] = f[x] + 1;
            g[x] = 0;
        } else {
            g[x] = max1 + 1;
        }
    }
}
int max[MAXN], tmp[MAXN], m;
inline int fuck(int i) {
    if (~tmp[i]) return tmp[i];
    return dp(i), tmp[i] = f[1];
}
int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    n = $();
    memset(head, -1, sizeof(head));
    memset(tmp, -1, sizeof(tmp));
    for (int i = 1; i < n; i++) $($(), $());
    for (m = 1; m * m < n;) m++;
    dfs(1);
    for (int i = 1; i <= m; i++) $(fuck(i)), pc(10);
    max[0] = n;
    for (int i = 1; i <= m; i++) {
        register int l = 1, r = max[i - 1];
        while (l <= r) {
            int mid = (l + r) >> 1;
            int val = fuck(mid);
            if (val >= i) {
                max[i] = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    for (int i = m + 1; i <= n; i++) {
        int l = 1, r = m, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (max[mid] >= i) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        $(ans);
        pc(10);
    }
    rt();
}