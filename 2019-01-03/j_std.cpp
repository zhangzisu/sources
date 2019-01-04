#include <bits/stdc++.h>
using lnt = long long;
std::map<lnt, int> M;
int m;
lnt n, S[10000], B[10000];
inline lnt h(lnt val) {
    val--;
    for (lnt i = 2; i * i <= val; i++) {
        if (val % i) continue;
        while (val % i == 0) val /= i;
        return val == 1 ? i : 0;
    }
    return val == 1 ? 0 : val;
}
int t, f[10000], g[10000], d[10000];
int main() {
    for (scanf("%d", &t); t; t--) {
        M.clear();
        m = 0;
        memset(g, 0, sizeof(g));
        scanf("%lld", &n);
        for (lnt i = 1; i * i <= n; i++) {
            if (n % i) continue;
            ++m, M[S[m] = i] = m, B[m] = h(i), d[m] = m;
            if (i * i == n) break;
            ++m, M[S[m] = n / i] = m, B[m] = h(n / i), d[m] = m;
        }
        std::sort(d + 1, d + m + 1, [](int a, int b) { return B[a] < B[b]; });
        g[M[1]] = 1;
        for (int _ = 1; _ <= m; _++) {
            const int& i = d[_];
            if (B[i] == 0) continue;
            if (B[i] != B[d[_ - 1]]) {
                memcpy(f, g, sizeof(f));
            }
            for (int j = 1; j <= m; j++) {
                if (!f[j]) continue;
                lnt where = S[j] * S[i];
                if (!M.count(where)) continue;
                g[M[where]] += f[j];
            }
        }
        printf("%d\n", g[M[n]]);
    }
    return 0;
}