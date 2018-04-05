#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 2010;
int n, X;
vector<int> G[N];
int dp[N][N], tmp[N], v[N], size[N];
void dfs(int u, int last) {
    size[u] = 1;
    //  for(int i = 0; i <= n; ++i) dp[u][i] = X - v[u];
    dp[u][0] = X - v[u];
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (v == last) continue;
        dfs(v, u);
        memset(tmp, -0x3f3f, sizeof(tmp));
        for (int j = 0; j <= size[u]; ++j)
            for (int k = 0; k <= size[v]; ++k) {
                tmp[j + k + 1] = max(tmp[j + k + 1], dp[u][j] + dp[v][k]);
                if (dp[v][k] >= 0) tmp[j + k] = max(tmp[j + k], dp[u][j]);
            }
        size[u] += size[v];
        for (int j = 0; j <= size[u] + 1; ++j) dp[u][j] = tmp[j];
    }
}
int main() {
    scanf("%d%d", &n, &X);
    for (int i = 1; i <= n; ++i) scanf("%d", &v[i]);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(dp, -0x3f3f, sizeof(dp));
    dfs(1, 0);
    for(int i=0;i<=n;i++)printf("%d ", dp[1][i]);
    puts("");
    for (int i = 0; i < n; ++i)
        if (dp[1][i] >= 0) {
            printf("%d\n", i);
            return 0;
        }
    return 0;
}