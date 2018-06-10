#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

typedef unsigned long long ulnt;
const int MAXSTAT = 43046721;
const int POOL = (MAXSTAT + 63) / 64;
int n, m, k, a[256], pw[10], ans = 0;

ulnt pool[10][POOL + 1];
int lastPos[10];
inline bool get(int x, int _Pos) { return (pool[x][_Pos / 64] >> (_Pos & 63)) & 1; }

inline void lshAndOr(int x, int y, int _Pos) {
    const int _Wordshift = _Pos >> 6;
    _Pos &= 63;
    const int __Pos = 64 - _Pos;
    const int Upper = std::min(POOL, lastPos[y] + _Wordshift);
    if (_Pos) {
        for (register int _Wpos = Upper; 0 <= _Wpos; --_Wpos) {
            pool[x][_Wpos] |= _Wordshift <= _Wpos ? ((pool[y][_Wpos - _Wordshift] << _Pos) | (pool[y][_Wpos - _Wordshift - 1] >> __Pos)) : (ulnt)0;
        }
    } else {
        for (register int _Wpos = Upper; 0 <= _Wpos; --_Wpos) {
            pool[x][_Wpos] |= _Wordshift <= _Wpos ? pool[y][_Wpos - _Wordshift] : (ulnt)0;
        }
    }
    lastPos[x] = std::max(lastPos[x], Upper);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    pw[0] = 1;
    for (int i = 1; i <= m; i++) pw[i] = pw[i - 1] * 9;
    for (int i = 0, x; i < n; i++) {
        scanf("%d", &x);
        for (int p = 0; p < m; p++) a[i] += ((x >> p) & 1) * pw[p];
    }
    std::sort(a, a + n);
    pool[0][0] = lastPos[0] = 1;
    for (register int i = 0; i < n; i++) {
        for (register int j = k - 1; ~j; j--) {
            lshAndOr(j + 1, j, a[i]);
        }
    }
    for (register int i = 0; i < pw[m]; i++) {
        if (get(k, i)) {
            int tmp = 0, val = i, dgt;
            for (register int j = 0; j < m; j++) {
                dgt = val % 9;
                tmp += dgt * dgt;
                val /= 9;
            }
            ans = std::max(ans, tmp);
        }
    }
    printf("%d\n", ans);
}