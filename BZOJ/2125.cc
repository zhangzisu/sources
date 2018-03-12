#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<functional>
#define MAXN 10010
#define MAXM 20010
#define $ long
typedef std::function<void($ $, $ $, $ $)> func;
struct Edges{
    $ $ head[MAXN], to[MAXM << 1], from[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot;
    inline Edges(){
        memset(head, -1, sizeof(head));
        tot = 0;
    }
    inline void operator () ($ $ u, $ $ v, $ $ w){
        next[tot] = head[u], to[tot] = v, from[tot] = u, val[tot] = w, head[u] = tot++;
        next[tot] = head[v], to[tot] = u, from[tot] = v, val[tot] = w, head[v] = tot++;
    }
    inline void operator () ($ $ x, func callback){
        for($ $ i = head[x];~i;i = next[i])callback(from[i], to[i], val[i]);
    }
}A, B;
$ $ n, m, q, cnt, dfn[MAXN], low[MAXN], top, _time = 0;
$ $ stk[MAXN], f[MAXN];
$ $ bel[MAXN], pel[MAXN], cln[MAXN];

inline void BuildC($ $ u, $ $ v, $ $ w){
    //printf("DDD %lld %lld %lld\n", u, v, w);
    cnt++; $ $ pre = w, id = 0;
    for($ $ i = v;i != f[u];i = f[i]){
        cln[i] = pre; pre += pel[i]; bel[i] = id++;
    }
    cln[cnt] = cln[u];
    cln[u] = 0;
    for($ $ i = v;i != f[u];i = f[i])B(cnt, i, std::min(cln[i], cln[cnt] - cln[i]));
}

void BuildCST($ $ x, $ $ fa){
    dfn[x] = low[x] = ++_time;
    A(x, [fa]($ $ u, $ $ v, $ $ length){
        if(v == fa)return;
        if(dfn[v]){
            low[u] = std::min(low[u], dfn[v]);
        }else{
            f[v] = u; pel[v] = length;
            BuildCST(v, u);
            low[u] = std::min(low[u], low[v]);
        }
        if(low[v] > dfn[u])B(u, v, length);
    });
    A(x, [fa]($ $ u, $ $ v, $ $ length){
        if(f[v] != u && dfn[v] > dfn[u]){
            BuildC(u, v, length);
        }
    });
}

$ $ deep[MAXN], dis[MAXN], pre[MAXN][18];
void DFS($ $ x, $ $ fa){
    B(x, [x, fa]($ $ u, $ $ v, $ $ length){
        if(v == fa)return;
        pre[v][0] = u;
        deep[v] = deep[u] + 1;
        dis[v] = dis[u] + length;
        DFS(v, u);
    });
}
inline $ $ LCA($ $ u, $ $ v, $ $ &x, $ $ &y){
    if(deep[u] > deep[v])std::swap(u, v);
    $ $ delta = deep[u] - deep[v];
    for($ $ i = 17;~i;i--)if((delta >> i) & 1)u = pre[u][i];
    for($ $ i = 17;~i;i--)if(pre[u][i] != pre[v][i])u = pre[u][i], v = pre[v][i];
    x = u; y = v;
    return u == v ? u : pre[u][0];
}



int main(){
    scanf("%lld%lld%lld", &n, &m, &q); cnt = n;
    for($ $ i = 1, u, v, w;i <= m;i++){
        scanf("%lld%lld%lld", &u, &v, &w); A(u, v, w);
    }
    BuildCST(1, 0);
    DFS(1, 0);
    while(q--){
        $ $ u, v, x, y; scanf("%lld%lld", &u, &v);
        $ $ lca = LCA(u, v, x, y);
        if(lca <= n){
            //circle-point
            printf("%lld\n", dis[u] + dis[v] - 2 * dis[lca]);
        }else{
            $ $ ans = dis[u] + dis[v] - dis[x] - dis[y];
            if(bel[x] > bel[y])std::swap(x, y);
            ans += std::min(cln[x] - cln[y] + cln[lca], cln[y] - cln[x]);
            printf("%lld\n", ans);
        }
    }
}