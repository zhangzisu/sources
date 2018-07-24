#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
int _5[40];
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
#define MAXN 1000010
int n, m, q, a[MAXN], p[MAXN], val[MAXN], pos[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
    // int start = clock();
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    n = getInt();
    m = getInt();
    q = getInt();
    for (int i = 1; i <= n; i++) a[i] = getInt();
    for (int i = 1; i <= m; i++) {
        p[i] = pos[i] = val[i] = i;
    }
    for (int a, b; q; q--) {
        a = getInt();
        b = getInt();
        int x = find(pos[a]);
        if (!x) continue;
        int y = find(pos[b]);
        if (x == y) continue;
        pos[a] = 0;
        if (!y) {
            pos[b] = x;
            val[x] = b;
        } else {
            pos[a] = 0;
            p[x] = y;
        }
    }
    for (int i = 1; i <= n; i++) {
        putInt(val[find(a[i])]);
        _putchar(i == n ? 10 : 32);
    }
    flush();
    // fprintf(stderr, "TIME SPENT: %lf ms\n", 1000. * (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}