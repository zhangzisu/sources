#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define INF 0x3F3F3F3F
int t, n, m, A[MAXN], B[MAXN];
std::set<int> S;
int fuck(int *a, int *b, int len, int &result) {
    int delta = b[1] - a[1];
    for (int i = 2; i <= len; i++)
        if (b[i] - a[i] != delta) return 0;
    result = delta;
    return 1;
}
int main() {
#ifndef DEBUG
    freopen("deviation.in", "r", stdin);
    freopen("deviation.out", "w", stdout);
#endif
    for (t = $(); t; t--) {
        n = $();
        for (int i = 1; i <= n; i++) A[i] = $();
        m = $();
        for (int i = 1; i <= m; i++) B[i] = $();
        int f1, f2, f3, f4, f5;
        f1 = 0;
        f2 = INF;
        f3 = 0;
        f4 = INF;
        f5 = 0;
        S.clear();
        for (int i = 1, result; i <= (n - m + 1); i++) {
            if (fuck(A + i - 1, B, m, result)) {
                S.insert(result);
                f2 = std::min(f2, std::abs(result));
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