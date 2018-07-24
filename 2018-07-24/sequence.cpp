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
int n, m, q, a[MAXN], b[MAXN], c[MAXN], p[MAXN];
int main() {
    n = getInt(), m = getInt(), q = getInt();
    for (register int i = 1; i <= n; i++) a[i] = getInt();
    for (register int i = 1; i <= m; i++) p[i] = i;
    for (register int i = 1; i <= q; i++) b[i] = getInt(), c[i] = getInt();
    for (register int i = q; i; i--) p[b[i]] = p[c[i]];
    for (register int i = 1; i <= n; i++) putInt(p[a[i]]), _putchar(i == n ? 10 : 32);
    return flush(), 0;
}