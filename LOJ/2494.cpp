#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 1000000007

inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int real;

struct bitset {
    const static int T = 5001;
    unsigned long long val[T / 64 + 1];
    inline void clear() { memset(val, 0, sizeof(val)); }
    inline void set(int x) { val[x >> 6] |= 1ULL << (x & 63); }
};

int n, m, q, bin[MAXN], ans, now, pre, c0, c1, flag;
bitset a[MAXN], v[MAXN], b, f[2][3], all, tmp, mask;

int main() {
    register char ch = getchar();
    bin[0] = 1;
    for (register int i = 1; i < MAXN; i++) bin[i] = 1LL * bin[i - 1] * 2 % MOD;
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) n = (n << 1) + (n << 3) + (ch ^ 48);
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) m = (m << 1) + (m << 3) + (ch ^ 48);
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) q = (q << 1) + (q << 3) + (ch ^ 48);

    real = (m - 1) / 64 + 1;
    for (register int i = 1; i <= n; i++) {
        while (!isdigit(ch)) ch = getchar();
        for (register int j = 0; j < m; j++) {
            if (ch ^ 48)
                a[i].set(j);
            else
                v[i].set(j);
            ch = getchar();
        }
    }
    for (register int i = 0; i < m; i++) all.set(i);
    while (q--) {
        b.clear();
        while (!isdigit(ch)) ch = getchar();
        for (int i = 0; i < m; i++) {
            if (ch ^ 48) b.set(i);
            ch = getchar();
        }
        c0 = 1;
        f[(n & 1) ^ 1][0].clear();
        ans = 0;
        for (int i = n; i; i--) {
            now = i & 1, pre = now ^ 1;
            c1 = c0, c0 = 0;
            for (int j = 0; j < c1; j++) {
                flag = 1;
                for (int k = 0; k < real; k++) {
                    tmp.val[k] = b.val[k] & (a[i].val[k] ^ b.val[k]);
                    if ((tmp.val[k] & f[pre][j].val[k]) != tmp.val[k]) goto fail0;
                    mask.val[k] = f[pre][j].val[k] | (v[i].val[k] ^ tmp.val[k]);
                    flag = flag && (mask.val[k] == all.val[k]);
                }
                if (!flag)
                    f[now][c0++] = mask;
                else
                    up(ans, bin[i - 1]);
            fail0:;
                flag = 1;
                for (int k = 0; k < real; k++) {
                    tmp.val[k] = a[i].val[k] & (a[i].val[k] ^ b.val[k]);
                    if ((tmp.val[k] & f[pre][j].val[k]) != tmp.val[k]) goto fail1;
                    mask.val[k] = f[pre][j].val[k] | (a[i].val[k] ^ tmp.val[k]);
                    flag = flag && (mask.val[k] == all.val[k]);
                }
                if (!flag)
                    f[now][c0++] = mask;
                else
                    up(ans, bin[i - 1]);
            fail1:;
            }
        }
        for (int i = 0; i < c0; i++) {
            for (int k = 0; k < real; k++)
                if (b.val[k] & (all.val[k] ^ f[1][i].val[k])) goto fail2;
            up(ans, 1);
        fail2:;
        }
        printf("%d\n", ans);
    }
    return 0;
}