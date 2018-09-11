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
#define MAXN 100010
#define MAXM 200010
int n, m, head[MAXN], to[MAXM], next[MAXM], in[MAXN], out[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    out[u]++, in[v]++;
}
int id[MAXN], val[MAXN], bfsclk = 0;
std::queue<int> Q;
int main() {
    freopen("duel.in", "r", stdin);
    freopen("duel.out", "w", stdout);
    memset(head, -1, sizeof(head));
    for (int u = n = $(), v = m = $(); m; m--) u = $(), v = $(), $(u, v);
    for (int i = 1; i <= n; i++)
        if (!in[i]) Q.push(i);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        id[++bfsclk] = x;
        for (int i = head[x]; ~i; i = next[i])
            if (!--in[to[i]]) Q.push(to[i]);
    }
    for (int i = 1; i <= n; i++)
        if (!out[i]) val[i] = $();
    for (int i = n; i >= 1; i--) {
        int x = id[i];
        if (out[x]) {
            bool all = 1;
            for (int i = head[x]; ~i; i = next[i]) all &= val[to[i]];
            val[x] = !all;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (val[i]) {
            _$('F'), _$('i'), _$('r'), _$('s'), _$('t'), _$(10);
        } else {
            _$('L'), _$('a'), _$('s'), _$('t'), _$(10);
        }
    }
    $_();
    return 0;
}
