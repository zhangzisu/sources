#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define $ 65536
char _1[$], *_3 = _1 + $;
inline char _getchar() {
    if (_3 == _1 + $) fread(_1, 1, $, stdin), _3 = _1;
    return *_3++;
}
inline int getInt() {
    register int __ = 0;
    register char _ = _getchar();
    while (!isdigit(_)) _ = _getchar();
    for (; isdigit(_); _ = _getchar()) __ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
    return __;
}

#define SQRT 320
#define MAXN 100010

int pri[SQRT], vis[SQRT], pnt = 0;
inline void shai() {
    for (int i = 2; i < SQRT; i++) {
        if (!vis[i]) {
            pri[++pnt] = i;
        }
        for (int j = 1; j <= pnt; j++) {
            if (i * pri[j] >= SQRT) break;
            vis[i * pri[j]] = 1;
            if (!(i % pri[j])) break;
        }
    }
}

int t, n, m, x[MAXN], sum[67][MAXN];
std::pair<int, int> fuck[MAXN];

int main() {
    shai();
    t = getInt();
    while (t--) {
        n = getInt();
        m = getInt();
        memset(sum, 0, sizeof(sum));

        for (int i = 1; i <= n; i++) {
            x[i] = getInt();
            for (int j = 1; j <= pnt; j++) {
                int d = 0;
                while (!(x[i] % pri[j])) d++, x[i] /= pri[j];
                sum[j][i] = sum[j][i - 1] + d;
            }
        }

        for (int i = 1; i <= n; i++) fuck[i] = {x[i], i};
        std::sort(fuck + 1, fuck + n + 1);
        while (m--) {
            int l = getInt(), r = getInt(), g = getInt();

            for (int i = 1; i <= pnt; i++) {
                int d = 0;
                while (!(g % pri[i])) d++, g /= pri[i];
                if (d > (sum[i][r] - sum[i][l - 1])) goto fail;
            }
            if (g != 1) {
                int pos = std::lower_bound(fuck + 1, fuck + n + 1, std::make_pair(g, l)) - fuck;
                if (pos > n || fuck[pos].first != g || fuck[pos].second > r) goto fail;
            }
            puts("Yes");
            continue;
        fail:
            puts("No");
        }
    }
    return 0;
}