#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
#define MOD 1000000007
int n, vi[MAXN], pr[MAXN], pnt = 0;
int pow[MAXN], ans[MAXN], res;
inline void shai() {
    for (int i = 2; i <= n; i++) {
        if (!vi[i]) pr[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pr[j] > n) break;
            vi[i * pr[j]] = 1;
            if (i % pr[j] == 0) break;
        }
    }
}
std::vector<int> su[MAXN];
void dfs(int x, int d, int v, int k) {
    if (d == (int)su[x].size()) return k <= 1 ? void() : ((ans[x] += 1LL * pow[d / v + 1] * (k & 1 ? 1 : MOD - 1) % MOD) %= MOD, void());
    dfs(x, d + 1, v, k);
    dfs(x, d + 1, v * su[x][d], k + 1);
}
int main() {
    scanf("%d", &n);
    ans[0] = pow[0] = 1;
    for (int i = 1; i <= n; i++) ans[i] = pow[i] = 2LL * pow[i - 1] % MOD;
    shai();
    for (int i = 2; i <= n; i++) {
        if (vi[i]) dfs(i, 0, 1, 0);
        (res += ans[i]) %= MOD;
        if (!vi[i])
            for (int j = 1; i * j <= n; j++) {
                su[i * j].push_back(i);
                (ans[i*j]+=)%=MOD;
            }
    }
    printf("%d\n", res);
    return 0;
}