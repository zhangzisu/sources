#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() {
    fwrite(_2, 1, _4 - _2, stdout);
    exit(0);
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline char _() {
    register char ch = gc();
    while (!isalpha(ch)) ch = gc();
    return ch;
}
inline void ps(const char *s) {
    for (; *s; s++) pc(*s);
    pc(10);
}
inline void $(int x) {
    static int _5[32];
    if (x == 0) return pc(48);
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
inline void $(long long x) {
    static int _5[64];
    if (x == 0) return pc(48);
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#include <deque>
#define MAXN 1000010
const int INF = 0x3F3F3F3F;
typedef long long lnt;
int n, m, a[MAXN], b[MAXN], c[MAXN], d[MAXN], e[MAXN], f[MAXN];
std::deque<int> Q;
lnt ans = 0;
int main() {
    freopen("wyt.in", "r", stdin);
    freopen("wyt.out", "w", stdout);

    n = $(), m = $();
    for (int i = 1; i <= n; i++) a[i] = $();
    for (int i = 1; i < m; i++) {
        while (Q.size() && a[Q.back()] > a[i]) Q.pop_back();
        Q.push_back(i);
    }
    for (int i = 1; i <= n - m + 1; i++) {
        while (Q.size() && a[Q.back()] >= a[i + m - 1]) Q.pop_back();
        Q.push_back(i + m - 1);
        b[i] = a[Q.front()];
        if (Q.front() == i) Q.pop_front();
        // fprintf(stderr, "%d ", b[i]);
    }
    // fprintf(stderr, "\n");
    Q.clear();
    for (int i = 1; i <= n; i++) {
        while (Q.size() && b[Q.back()] <= b[i]) Q.pop_back();
        Q.push_back(i);
        c[i] = b[e[i] = Q.front()];
        ans += a[i] - c[i];
        if (Q.front() == i - m + 1) Q.pop_front();
        // fprintf(stderr, "[%d,%d] ", c[i], e[i]);
    }
    // fprintf(stderr, "\n");
    $(ans), pc(10);
    Q.clear();
    Q.push_back(n + 1);
    c[n + 1] = INF;
    for (int i = n; i; i--) {
        while (Q.size() && c[Q.back()] <= c[i]) Q.pop_back();
        d[i] = Q.back();
        Q.push_back(i);
        // fprintf(stderr, "%d ", d[i]);
    }
    // fprintf(stderr, "\n");
    memset(f, 0x3F, sizeof(f));
    f[1] = 0;
    for (int i = 1; i <= n; i++) {
        int next = std::min(e[i] + m, d[i]);
        f[next] = std::min(f[next], f[i] + 1);
    }
    $(f[n + 1]), pc(10);
    rt();
}