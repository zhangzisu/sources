#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXSTAT = 43046721;
const int POOL = (MAXSTAT + 63) / 64;
int n, m, k, a[256], pw[10], ans = 0;
typedef unsigned long long ulnt;

struct bitset {
    long long pool[POOL];
    inline bitset() {
        memset(pool, 0, sizeof(pool));
    }
    inline bitset(const bitset &o) {
        memcpy(pool, o.pool, sizeof(pool));
    }
    inline bool get(int pos) {
        int shift = pos / 64;
        int bpos = pos & 63;
        long long &x = pool[shift];
        return (x >> bpos) & 1;
    }
    inline void set(int pos, int val) {
        int shift = pos / 64;
        int bpos = pos & 63;
        long long &x = pool[shift];
        x = (x >> (bpos + 1) << (bpos + 1)) | (val << bpos) | (x & ((1 << bpos) - 1));
    }
    inline void lsh(int _Pos) {
        const int _Wordshift = (int)(_Pos / 64);
        if (_Wordshift != 0)
            for (int _Wpos = POOL; 0 <= _Wpos; --_Wpos)
                pool[_Wpos] = _Wordshift <= _Wpos ? pool[_Wpos - _Wordshift] : (ulnt)0;

        if ((_Pos %= 64) != 0) {
            for (int _Wpos = POOL; 0 < _Wpos; --_Wpos)
                pool[_Wpos] = (ulnt)((pool[_Wpos] << _Pos) | (pool[_Wpos - 1] >> (64 - _Pos)));
            pool[0] <<= _Pos;
        }
    }
    inline void rsh(int _Pos) {
        const int _Wordshift = (int)(_Pos / 64);
        if (_Wordshift != 0)
            for (int _Wpos = 0; _Wpos <= POOL; ++_Wpos)
                pool[_Wpos] = _Wordshift <= POOL - _Wpos ? pool[_Wpos + _Wordshift] : (ulnt)0;

        if ((_Pos %= 64) != 0) {
            for (int _Wpos = 0; _Wpos < POOL; ++_Wpos)
                pool[_Wpos] = (ulnt)((pool[_Wpos] >> _Pos) | (pool[_Wpos + 1] << (64 - _Pos)));
            pool[POOL] >>= _Pos;
        }
    }
    inline void orEql(const bitset &o) {
        for (int _Wpos = 0; _Wpos < POOL; _Wpos++) pool[_Wpos] |= o.pool[_Wpos];
    }
    inline void setAll(const bitset &o) {
        memcpy(pool, o.pool, sizeof(pool));
    }
} f[10], tmp;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    pw[0] = 1;
    for (int i = 1; i <= m; i++) pw[i] = pw[i - 1] * (k + 1);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    std::sort(a, a + n);

    f[0].set(0, 1);
    for (int i = 0; i < n; i++) {
        int delta = 0;
        for (int p = 0; p < m; p++) delta += ((a[i] >> p) & 1) * pw[p];
        for (int j = k - 1; ~j; j--) {
            tmp.setAll(f[j]);
            tmp.lsh(delta);
            f[j + 1].orEql(tmp);
        }
    }

    int ans = 0;
    for (int i = 0; i < pw[m]; i++) {
        if (f[k].get(i)) {
            int tmp = 0;
            for (int j = 0; j < m; j++) {
                int val = i / pw[j] % (k + 1);
                tmp += val * val;
            }
            ans = std::max(ans, tmp);
            if (tmp >= 100) printf("%d => %d\n", i, tmp);
        }
    }
    printf("%d\n", ans);
}