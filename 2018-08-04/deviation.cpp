#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define INF 0x3F3F3F3F
int t, n, m, A[MAXN], B[MAXN], a[MAXN], b[MAXN];
unsigned BASE[2] = {105137, 233}, MOD[2] = {1000000787, 1000000241};
unsigned HASH[2][MAXN], ORI[2][MAXN], POW[2][MAXN];
inline unsigned GET_HASH(unsigned *arr, int l, int r, int hid) {
    return (arr[r] - 1ULL * arr[l - 1] * POW[hid][r - l + 1] % MOD[hid] + MOD[hid]) % MOD[hid];
}
std::set<int> S;
std::vector<int> V;
int main() {
#ifndef DEBUG
    freopen("deviation.in", "r", stdin);
    freopen("deviation.out", "w", stdout);
#endif
    POW[0][0] = POW[1][0] = 1;
    for (int i = 1; i < MAXN; i++) {
        POW[0][i] = 1ULL * POW[0][i - 1] * BASE[0] % MOD[0];
        POW[1][i] = 1ULL * POW[1][i - 1] * BASE[1] % MOD[1];
    }
    for (t = $(); t; t--) {
        S.clear();
        n = $();
        for (int i = 1; i <= n; i++) A[i] = $();
        m = $();
        for (int i = 1; i <= m; i++) B[i] = $();
        V.clear();
        for (int i = 1; i < n; i++) V.push_back(a[i] = A[i + 1] - A[i]);
        for (int i = 1; i < m; i++) V.push_back(b[i] = B[i + 1] - B[i]);
        n--, m--;
        std::sort(V.begin(), V.end());
        for (int i = 1; i <= n; i++) a[i] = std::lower_bound(V.begin(), V.end(), a[i]) - V.begin();
        for (int i = 1; i <= m; i++) b[i] = std::lower_bound(V.begin(), V.end(), b[i]) - V.begin();
        for (int i = 1; i <= n; i++) {
            HASH[0][i] = (1ULL * HASH[0][i - 1] * BASE[0] + a[i]) % MOD[0];
            HASH[1][i] = (1ULL * HASH[1][i - 1] * BASE[1] + a[i]) % MOD[1];
        }
        for (int i = 1; i <= m; i++) {
            ORI[0][i] = (1ULL * ORI[0][i - 1] * BASE[0] + b[i]) % MOD[0];
            ORI[1][i] = (1ULL * ORI[1][i - 1] * BASE[1] + b[i]) % MOD[1];
        }
        int f1, f2, f3, f4, f5;
        f1 = 0;
        f2 = INF;
        f3 = 0;
        f4 = INF;
        f5 = 0;
        for (int i = 1; i <= (n - m + 1); i++) {
            unsigned hA = GET_HASH(HASH[0], i, i + m - 1, 0);
            unsigned hB = GET_HASH(HASH[1], i, i + m - 1, 1);
            if (hA == ORI[0][m] && hB == ORI[1][m]) {
                S.insert(B[1] - A[i]);
                f2 = std::min(f2, std::abs(B[1] - A[i]));
                f3++;
                f4 = std::min(f4, i);
                f5 = std::max(f5, i);
            }
        }
        f1 = S.size();
        if (!f1)
            puts("0 0 0 0 0");
        else
            printf("%d %d %d %d %d\n", f1, f2, f3, f4, f5);
    }
    return 0;
}