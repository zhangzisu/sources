#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define D 65536
char _1[D], _2[D], *_3 = _1 + D, *_4 = _2;
inline char _getchar() {
    if (_3 == _1 + D) fread(_1, 1, D, stdin), _3 = _1;
    return *_3++;
}
inline int getInt() {
    register int __ = 0;
    register char _ = _getchar();
    while (!isdigit(_)) _ = _getchar();
    for (; isdigit(_); _ = _getchar()) __ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
    return __;
}
inline void _putchar(char c) {
    if (_4 == _2 + D) fwrite(_2, 1, D, stdout), _4 = _2;
    *_4++ = c;
}
int _5[32];
inline void putInt(int x) {
    if (x == 0) {
        _putchar('0');
        return;
    }
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) _putchar(_5[_6--] ^ 48);
}
inline void flush() { fwrite(_2, 1, _4 - _2, stdout); }
#define err(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MAXN 100010
#define MAXK 5000010
int n, m, head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int size[MAXN], fa[MAXN], deep[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], dfsclk = 0;
void dfs(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
}
void split(int x) {
    pos[dfn[x] = ++dfsclk] = x;
    if (!~top[x]) top[x] = x;
    int max = n + 1;
    for (int i = head[x]; ~i; i = next[i])
        if (size[to[i]] > size[max]) max = to[i];
    if (max <= n) {
        top[max] = top[x];
        split(max);
    }
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != max) split(to[i]);
}
int sum[MAXK], L[MAXK], R[MAXK], tot = 0;
//
int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    // int start = clock();
    memset(head, -1, sizeof(head));
    memset(top, -1, sizeof(top));
    n = getInt();
    n++;
    for (int i = 2; i <= n; i++) $(getInt() + 1, i);
    dfs(1);
    split(1);
    m = getInt();
    for (int i = 1, op; i <= m; i++) {
        op = getInt();
        if (op == 1)
            add(i);
        else
            qry(i);
    }
    // err("%lf\n", 1. * (clock() - start) / CLOCKS_PER_SEC);
    flush();
    return 0;
}