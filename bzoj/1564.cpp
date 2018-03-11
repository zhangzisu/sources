#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100
int n, k;
const long long INF = (~(unsigned long long)0) >> 1;
struct node {
    int dat, val, frc;
    inline friend bool operator<(const node &a, const node &b) {
        return a.dat < b.dat;
    }
} tr[MAXN];
std::vector<int> V;
long long f[MAXN][MAXN][MAXN], pfx[MAXN];
long long DP(int l, int r, int m) {
    if (l > r) return 0;
    if (~f[l][r][m]) return f[l][r][m];
    long long ret = INF;
    for (int i = l; i <= r; i++) {
        ret = std::min(ret, DP(l, i - 1, m) + DP(i + 1, r, m) + k);
        if (tr[i].val >= m) ret = std::min(ret, DP(l, i - 1, tr[i].val + 1) + DP(i + 1, r, tr[i].val + 1));
    }
    return f[l][r][m] = ret + pfx[r] - pfx[l - 1];
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &tr[i].dat);
    for (int i = 1; i <= n; i++) scanf("%d", &tr[i].val), V.push_back(tr[i].val);
    for (int i = 1; i <= n; i++) scanf("%d", &tr[i].frc);
    std::sort(tr + 1, tr + n + 1);
    std::sort(V.begin(), V.end());
    V.erase(std::unique(V.begin(), V.end()), V.end());
    for (int i = 1; i <= n; i++) tr[i].val = std::lower_bound(V.begin(), V.end(), tr[i].val) - V.begin();
    for (int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + tr[i].frc;
    memset(f, -1, sizeof(f));
    printf("%lld\n", DP(1, n, 0));
    return 0;
}