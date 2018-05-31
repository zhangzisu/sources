#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define _$_ 65536
char _1[_$_], _2[_$_], *_3 = _1 + _$_, *_4 = _2;
inline char _getchar() {
    if (_3 == _1 + _$_) fread(_1, 1, _$_, stdin), _3 = _1;
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
    if (_4 == _2 + _$_) fwrite(_2, 1, _$_, stdout), _4 = _2;
    *_4++ = c;
}
int _5[65];
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
#define MAXN 200010
#define MAXM 8000010

const int base = 23;

int T, n, m, a[MAXN], maxA;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;

inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN][18], deep[MAXN];
int root[MAXN], L[MAXM], R[MAXM], cnt = 0;
unsigned hash0[MAXM], hash1[MAXM], wop[MAXN];
void build(int &x, int l, int r) {
    x = ++cnt;
    if (l == r) return hash0[x] = 0, hash1[x] = 1, void();
    int mid = (l + r) >> 1;
    build(L[x], l, mid);
    build(R[x], mid + 1, r);
    hash0[x] = hash0[L[x]] + wop[mid - l + 1] * hash0[R[x]];
    hash1[x] = hash1[L[x]] + wop[mid - l + 1] * hash1[R[x]];
}
void reverse(int &x, int y, int l, int r, int p) {
    x = ++cnt;
    L[x] = L[y], R[x] = R[y];
    if (l == r) return hash0[x] = hash1[y], hash1[x] = hash0[y], void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        reverse(L[x], L[y], l, mid, p);
    else
        reverse(R[x], R[y], mid + 1, r, p);
    hash0[x] = hash0[L[x]] + wop[mid - l + 1] * hash0[R[x]];
    hash1[x] = hash1[L[x]] + wop[mid - l + 1] * hash1[R[x]];
}

int getAns(int x, int y, int l, int r) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (hash0[L[x]] ^ hash1[L[y]])
        return getAns(L[x], L[y], l, mid);
    return getAns(R[x], R[y], mid + 1, r);
}

void dfs(int x) {
    reverse(root[x], root[fa[x][0]], 1, maxA, a[x]);
    for (int i = 1; i < 18; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
    }
}
inline int LCA(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = 17; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    for (int i = 17; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
inline void reset_env() {
    memset(head, -1, sizeof(head));
    tot = cnt = maxA = 0;
}

int main() {
    T = getInt();
    wop[0] = 1;
    for (int i = 1; i < MAXN; i++) wop[i] = wop[i - 1] * base;
    while (T--) {
        reset_env();
        n = getInt(), m = getInt();
        for (int i = 1; i <= n; i++) maxA = std::max(maxA, a[i] = getInt());
        for (int i = 1; i < n; i++) $(getInt(), getInt());
        maxA++;
        build(root[0], 1, maxA);
        dfs(1);
        while (m--) {
            int u = getInt(), v = getInt();
            int lca = LCA(u, v), tmp;
            reverse(tmp, root[u], 1, maxA, a[lca]);
            putInt(getAns(tmp, root[v], 1, maxA));
            _putchar(10);
        }
    }
    flush();
}