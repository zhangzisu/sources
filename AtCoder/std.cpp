#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define pii pair<int, int>
#define mk make_pair
#define pb push_back
#define eps 1e-12
#define sd(x) scanf("%d", &x)
#define sdl(x) scanf("%lld", &x)
#define pd(x) printf("%d\n", x)
#define pdl(x) printf("%lld\n", x)
#define MAXN 200009
using namespace std;
vector<int> g[MAXN];
int deg[MAXN];
vector<int> edge_list[MAXN];
pii edge[MAXN];
bool no_use[MAXN];
int new_deg[MAXN];
int dist[MAXN];
int par[MAXN];
int final_dist[MAXN];
inline void dfs(int pos, int prev) {
    dist[pos] = dist[prev] + 1;
    for (int i = 0; i < g[pos].size(); i++) {
        if (g[pos][i] != prev) {
            dfs(g[pos][i], pos);
        }
    }
}
inline void dfs1(int pos, int prev) {
    par[pos] = prev;
    final_dist[pos] = final_dist[prev] + 1;
    for (int i = 0; i < g[pos].size(); i++) {
        if (g[pos][i] != prev) {
            dfs1(g[pos][i], pos);
        }
    }
}
int main() {
    int n;
    sd(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        sd(x);
        sd(y);
        g[x].pb(y);
        g[y].pb(x);
        deg[x]++;
        deg[y]++;
        edge[i] = mk(x, y);
        edge_list[x].pb(i);
        edge_list[y].pb(i);
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            no_use[edge_list[i][0]] = true;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!no_use[i]) {
            new_deg[edge[i].first]++;
            new_deg[edge[i].second]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (new_deg[i] >= 3) {
            printf("-1\n");
            return 0;
        }
    }
    dfs(1, 0);
    int maxid = -1;
    int maxx = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > maxx) {
            maxx = dist[i];
            maxid = i;
        }
    }
    dfs1(maxid, 0);
    maxx = 0;
    maxid = -1;
    for (int i = 1; i <= n; i++) {
        if (final_dist[i] > maxx) {
            maxx = final_dist[i];
            maxid = i;
        }
    }
    vector<int> v;
    int val = maxid;
    while (val) {
        v.pb(val);
        val = par[val];
    }
    vector<int> fans1, fans2;
    int next_num = 1;
    for (int i = 0; i < v.size(); i++) {
        int req = deg[v[i]];
        if ((i == 0) || (i == (v.size() - 1))) {
            req--;
        } else {
            req -= 2;
        }
        for (int i = next_num + 1; i <= next_num + req; i++) {
            fans1.pb(i);
        }
        fans1.pb(next_num);
        next_num = next_num + req + 1;
    }
    reverse(v.begin(), v.end());
    next_num = 1;
    for (int i = 0; i < v.size(); i++) {
        int req = deg[v[i]];
        if ((i == 0) || (i == (v.size() - 1))) {
            req--;
        } else {
            req -= 2;
        }
        for (int i = next_num + 1; i <= next_num + req; i++) {
            fans2.pb(i);
        }
        fans2.pb(next_num);
        next_num = next_num + req + 1;
    }
    vector<int> res;
    if (fans1 < fans2) {
        res = fans1;
    } else {
        res = fans2;
    }
    for (int i = 0; i < res.size(); i++) {
        printf("%d%c", res[i], " \n"[i==res.size()-1]);
    }
    printf("\n");
    return 0;
}
