#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char _$() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int __ = 0;
    register char _ = _$();
    while (!isdigit(_)) _ = _$();
    for (; isdigit(_); _ = _$()) __ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
    return __;
}
inline void _$(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void $(int x) {
    if (x == 0) return _$('0');
    static int _5[32];
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) _$(_5[_6--] ^ 48);
}
inline void $(long long x) {
    if (x == 0) return _$('0');
    static int _5[64];
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) _$(_5[_6--] ^ 48);
}
inline void $_() { fwrite(_2, 1, _4 - _2, stdout); }
#include <queue>
#define MAXN 200010
#define MAXM 400010
typedef long long lnt;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, m, k, s;
lnt dis[MAXN];
std::priority_queue<std::pair<lnt, int> > Q;
inline void $$() {
    memset(dis, 0x3F, sizeof(dis));
    Q.push(std::make_pair(dis[s] = 0, s));
    while (Q.size()) {
        std::pair<lnt, int> top = Q.top();
        Q.pop();
        if (-top.first != dis[top.second]) continue;
        for (int i = head[top.second]; ~i; i = next[i]) {
            if (val[i] - top.first < dis[to[i]]) {
                Q.push(std::make_pair(-(dis[to[i]] = val[i] - top.first), to[i]));
            }
        }
    }
}
int main() {
    freopen("transprt.in", "r", stdin);
    freopen("transprt.out", "w", stdout);
    n = $(), m = $(), k = $(), s = $();
    memset(head, -1, sizeof(head));
    for (int u, v, w; m; m--) u = $(), v = $(), w = $(), $(u, v, w * 2);
    m = n;
    for (int b, t; k; k--) {
        b = $(), t = $(), ++m;
        while (t--) $($(), m, b);
    }
    $$();
    for (int i = 1; i <= n; i++) $(dis[i] / 2), _$(' ');
    _$(10);
    $_();
    return 0;
}