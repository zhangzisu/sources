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
#define MAXN 500010
#define MOD 1000000007
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int lowbit(int x) { return x & -x; }
inline void add(int *bit, int x, int v, int n) {
    for (; x <= n; x += lowbit(x)) up(bit[x], v);
}
inline int qry(int *bit, int x, int n) {
    int v = 0;
    for (; x; x -= lowbit(x)) up(v, bit[x]);
    return v;
}
int n, l, a, b, ans = 1, x[MAXN], bit1[MAXN], bit2[MAXN];
int main() {
    freopen("gg.in", "r", stdin);
    freopen("gg.out", "w", stdout);

    n = $(), l = $(), x[0] = $(), a = $(), b = $();
    x[0] %= l;
    add(bit1, x[0] + 1, 1, l);
    add(bit2, x[0] + 1, x[0], l);
    for (int i = 1; i < n; i++) {
        x[i] = (1LL * x[i - 1] * a + b) % l;
        int leftcnt = qry(bit1, x[i] + 1, l);
        int rightcnt = qry(bit1, l, l) - leftcnt;
        int leftsum = qry(bit2, x[i] + 1, l);
        int rightsum = (qry(bit2, l, l) - leftsum + MOD) % MOD;
        ans = (1LL * ans * (1LL * leftcnt * x[i] % MOD - leftsum + rightsum - 1LL * rightcnt * x[i] % MOD) % MOD + MOD) % MOD;
        add(bit1, x[i] + 1, 1, l);
        add(bit2, x[i] + 1, x[i], l);
    }
    $(ans), pc(10);
    rt();
}