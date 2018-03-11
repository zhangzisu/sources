#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 300010
int t, n, m, cnt;
std::pair<int, int> p[MAXN];
int P[MAXN], ans, res0, root[MAXN];
inline int find(int x) { return x == P[x] ? x : P[x] = find(P[x]); }
int fa[MAXN][18], son[MAXN][2], low[MAXN];
std::vector<std::pair<int, int>> pa[MAXN];
int f[MAXN], g[MAXN];

void DFS(int x) {
    int cnt0 = 0, cnt1 = 0;
    for (auto i : pa[x]) (i.second ? cnt1 : cnt0)++;
    if (!son[x][0] && !son[x][1]) {
        std::sort(pa[x].begin(), pa[x].end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first < b.first; });
        int max = cnt0, mmax = 0;
        for (int i = 0; i < (int)pa[x].size(); i++) {
            mmax = std::max(mmax, max);
            if (pa[x][i].second)
                max++;
            else
                max--;
        }
        mmax = std::max(mmax, max);
        f[x] = cnt1;
        g[x] = std::max(cnt0, mmax);
        return;
    }
    DFS(son[x][0]);
    DFS(son[x][1]);
    f[x] = f[son[x][0]] + f[son[x][1]] + cnt1;
    g[x] = g[son[x][0]] + g[son[x][1]] + cnt0;
    std::sort(pa[x].begin(), pa[x].end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first < b.first; });
    int max = cnt0, mmax = 0;
    for (int i = 0; i < (int)pa[x].size(); i++) {
        mmax = std::max(mmax, max);
        if (pa[x][i].second)
            max++;
        else
            max--;
    }
    mmax = std::max(mmax, max);
    g[x] = std::max(g[x], f[son[x][0]] + f[son[x][1]] + mmax);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1;i <= cnt;i++)pa[i].clear();
        cnt = n;
        ans = 0;
        memset(fa, 0, sizeof(fa));
        memset(son, 0, sizeof(son));
        memset(low, 0, sizeof(low));
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));

        for (int i = 1; i < n; i++) {
            scanf("%d", &p[i].first);
            p[i].second = i;
        }
        for (int i = 1; i <= n; i++) root[P[i] = i] = i;
        std::sort(p + 1, p + n);
        for (int i = 1; i < n; i++) {
            int L = p[i].second, R = p[i].second + 1;
            int LL = find(L), RR = find(R);
            ++cnt;
            son[cnt][0] = root[LL];
            son[cnt][1] = root[RR];
            fa[root[LL]][0] = cnt;
            // printf("%d => %d\n", cnt, root[LL]);
            fa[root[RR]][0] = cnt;
            // printf("%d => %d\n", cnt, root[RR]);
            root[P[LL] = RR] = cnt;
            low[cnt] = p[i].first;
        }
        for (int d = 1; d < 18; d++)
            for (int i = 1; i <= cnt; i++)
                fa[i][d] = fa[fa[i][d - 1]][d - 1];
        low[0] = 0x7FFFFFFF;
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            y++;
            for (int i = 17; ~i; i--)
                if (low[fa[x][i]] < y) x = fa[x][i];
            pa[x].push_back(std::make_pair(y, z));
            // printf("%d => (%d, %d)\n", x, y, z);
        }
        DFS(cnt);
        printf("%d\n", std::max(f[cnt], g[cnt]));
    }
    return 0;
}