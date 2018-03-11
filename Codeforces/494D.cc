#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
#define MOD 1000000007
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w){
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int deep[MAXN], fa[MAXN][19], n, q;
long long dis[MAXN], S0[MAXN], S1[MAXN], S2[MAXN], S3[MAXN], S4[MAXN];

void dfs(int x){
    S0[x] = 1;
    for(int i = head[x];~i;i = next[i]){
        if(to[i] == fa[x][0])continue;
        deep[to[i]] = deep[x] + 1;
        dis[to[i]] = dis[x] + val[i];
        fa[to[i]][0] = x;
        dfs(to[i]);
        S0[x] += S0[to[i]];
        S1[x] += S1[to[i]] + S0[to[i]] * val[i] % MOD;
        S1[x] %= MOD;
        S2[x] += S2[to[i]] + S0[to[i]] * val[i] % MOD * val[i] % MOD + S1[to[i]] * 2 * val[i] % MOD;
        S2[x] %= MOD;
    }
}
void DFS(int x){
    S3[x] = S2[x]; S4[x] = S1[x];
    for(int i = head[x];~i;i = next[i]){
        if(to[i] == fa[x][0])continue;
        long long B$ = S1[x], B2 = S2[x], BS = S0[x];
        long long C$ = S1[to[i]], C2 = S2[to[i]], CS = S0[to[i]];
        S0[x] -= S0[to[i]];
        S0[x] %= MOD;
        S1[x] -= S1[to[i]] + S0[to[i]] * val[i] % MOD;
        S1[x] %= MOD;
        S2[x] -= S2[to[i]] + S0[to[i]] * val[i] % MOD * val[i] % MOD + S1[to[i]] * 2 * val[i] % MOD;
        S2[x] %= MOD;
        (S0[x] += MOD) %= MOD;
        (S1[x] += MOD) %= MOD;
        (S2[x] += MOD) %= MOD;
        S0[to[i]] += S0[x];
        S0[to[i]] %= MOD;
        S1[to[i]] += S1[x] + S0[x] * val[i] % MOD;
        S1[to[i]] %= MOD;
        S2[to[i]] += S2[x] + S0[x] * val[i] % MOD * val[i] % MOD + S1[x] * 2 * val[i] % MOD;
        S2[to[i]] %= MOD;
        (S0[to[i]] += MOD) %= MOD;
        (S1[to[i]] += MOD) %= MOD;
        (S2[to[i]] += MOD) %= MOD;
        DFS(to[i]);
        S1[x] = B$; S2[x] = B2; S0[x] = BS;
        S1[to[i]] = C$; S2[to[i]] = C2; S0[to[i]] = CS;
    }
}

inline int LCA(int u, int v){
    if(deep[u] < deep[v])std::swap(u, v);
    int delta = deep[u] - deep[v];
    for(int i = 18;~i;i--)if((delta >> i) & 1)u = fa[u][i];
    for(int i = 18;~i;i--)if(fa[u][i] != fa[v][i])u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}

int main(){
    scanf("%d", &n); memset(head, -1, sizeof(head));
    for(int i = 1, x, y, z;i < n;i++){
        scanf("%d%d%d", &x, &y, &z);
        $(x, y, z);
    }
    dfs(1); DFS(1); scanf("%d", &q);
    for(int d = 1;d <= 18;d++){
        for(int i = 1;i <= n;i++){
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
        }
    }
    while(q--){
        int u, v; scanf("%d%d", &u, &v);
        long long ans;
        int lca = LCA(u, v);
        long long tmp = (dis[u] + dis[v] - 2 * dis[lca] % MOD) % MOD;
        if(lca == v){
            ans = S3[u];
            ans -= (tmp * tmp % MOD * (n - S0[v]) % MOD + (S3[v] - S2[v]) + 2 * tmp * (S4[v] - S1[v]) % MOD) * 2 % MOD;
        }else{
            ans = (tmp * tmp % MOD * S0[v] % MOD + S2[v] + 2 * tmp * S1[v] % MOD) * 2 % MOD;
			ans -= S3[u];
        }
        ans %= MOD;
        ans += MOD;
        ans %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}