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
#define MAXN 1000010
const int MOD1 = 1000000009;
const int MOD2 = 1000000007;
const int BASE1 = 29;
const int BASE2 = 31;
int n, m, a[MAXN], hash1[MAXN], hash2[MAXN], pow1[MAXN], pow2[MAXN], as1, as2, asp, as;
inline int cb1(int x, int y) {
    return x + y >= MOD1 ? x + y - MOD1 : x + y;
}
inline int cb2(int x, int y) {
    return x + y >= MOD2 ? x + y - MOD2 : x + y;
}
inline int getHash1(int l, int r) {
    return cb1(hash1[r], MOD1 - 1LL * hash1[l - 1] * pow1[r - l + 1] % MOD1);
}
inline int getHash2(int l, int r) {
    return cb2(hash2[r], MOD2 - 1LL * hash2[l - 1] * pow2[r - l + 1] % MOD2);
}
int main() {
    freopen("lgg.in", "r", stdin);
    freopen("lgg.out", "w", stdout);

    pow1[0] = pow2[0] = 1;
    for (register int i = 1; i < MAXN; i++) pow1[i] = 1LL * pow1[i - 1] * BASE1 % MOD1;
    for (register int i = 1; i < MAXN; i++) pow2[i] = 1LL * pow2[i - 1] * BASE2 % MOD2;
    for (int t = $(); t; t--) {
        n = $();
        if (n % 2 == 0) {
            puts("NOT POSSIBLE");
            continue;
        }
        m = (n - 1) / 2;
        as = 0;
        for (register int i = 1; i <= n; i++) a[i] = _() - 'A';
        for (register int i = 1; i <= n; i++) hash1[i] = cb1(1LL * hash1[i - 1] * BASE1, a[i]);
        for (register int i = 1; i <= n; i++) hash2[i] = cb2(1LL * hash2[i - 1] * BASE2, a[i]);
        int HSL1 = getHash1(1, m);
        int HSL2 = getHash2(1, m);
        int HSR1 = getHash1(m + 2, n);
        int HSR2 = getHash2(m + 2, n);
        for (register int i = 1, hsl1, hsl2, hsr1, hsr2; i <= n; i++) {
            if (i == m + 1) {
                hsl1 = HSL1;
                hsl2 = HSL2;
                hsr1 = HSR1;
                hsr2 = HSR2;
            } else if (i <= m) {
                hsl1 = cb1(1LL * getHash1(1, i - 1) * pow1[m - i + 1] % MOD1, getHash1(i + 1, m + 1));
                hsl2 = cb2(1LL * getHash2(1, i - 1) * pow2[m - i + 1] % MOD2, getHash2(i + 1, m + 1));
                hsr1 = HSR1;
                hsr2 = HSR2;
            } else {
                hsl1 = HSL1;
                hsl2 = HSL2;
                hsr1 = cb1(1LL * getHash1(m + 1, i - 1) * pow1[n - i] % MOD1, getHash1(i + 1, n));
                hsr2 = cb2(1LL * getHash2(m + 1, i - 1) * pow2[n - i] % MOD2, getHash2(i + 1, n));
            }
            if (hsl1 == hsr1 && hsl2 == hsr2) {
                if (!as) {
                    as = 1, as1 = hsl1, as2 = hsl2, asp = i;
                } else {
                    if (as1 != hsl1 || as2 != hsl2) {
                        ps("NOT UNIQUE");
                        as = 2;
                        break;
                    }
                }
            }
        }
        if (!as) {
            ps("NOT POSSIBLE");
        } else if (as == 1) {
            for (int i = 1; i <= m; i++) {
                if (i == asp) {
                    m++;
                } else {
                    pc(a[i] + 'A');
                }
            }
            pc(10);
        }
    }
    rt();
}