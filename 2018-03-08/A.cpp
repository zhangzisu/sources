// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
const int MOD = 1000000007;
const int MAXN = 200010;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
int size[MAXN], frc[MAXN], inv[MAXN];
inline void $(int u, int v){
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline int C(int n, int m) {
    if(n < m)return 0;
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int n, ans[MAXN];
inline void add(int &n, int x){n += x;if(n >= MOD)n -= MOD;}
inline void del(int &n, int x){n -= x;if(n < 0)n += MOD;}
std::vector<int> V;
void dfs(int x, int fa){
    size[x] = 1;
    for(int i = head[x];~i;i = next[i]){
        if(to[i] == fa)continue;
        dfs(to[i], x);
        size[x] += size[to[i]];
        V.push_back(size[to[i]]);
        V.push_back(n - size[to[i]]);
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    memset(head, -1, sizeof(head));
    frc[0] = 1;
    register int i, now = 0;
    int u, v;
    for(i = 1;i < MAXN;i++)frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = 758835755;
    for(i = MAXN - 1;i;i--)inv[i - 1] = 1LL * inv[i] * i % MOD;
    std::cin >> n;
    for(i = 1;i <= n;i++){
        add(ans[i], C(n, i));
        ans[i] = 1LL * (n - 1) * ans[i] % MOD;
        add(ans[i], C(n, i));
    }
    for(i = 1;i < n;i++){
        std::cin >> u >> v;
        $(u, v);
    }
    dfs(1, 0);
    for(i = 0;i < (int)V.size();i++){
        now++;
        if(i + 1 == (int)V.size() || V[i] != V[i + 1]){
            for(int j = 1;j <= V[i];j++){
                del(ans[j], 1LL * now * C(V[i], j) % MOD);
            }
            now = 0;
        }
    }
    for(i = 1;i <= n;i++)std::cout << ans[i] << std::endl;
    return 0;
}