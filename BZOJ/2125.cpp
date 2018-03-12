#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
//#include<functional>
#define MAXN 500010
#define MAXM 1000010
#define $ long
//typedef std::function<void($ $, $ $, $ $)> func;
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
    // inline void operator () ($ $ x, func callback){
    //     for(int i = head[x];~i;i = next[i])callback(from[i], to[i], val[i]);
    // }
}A, B;
$ $ n, m, q, cnt, dfn[MAXN], low[MAXN], top, _time = 0;
$ $ stk[MAXN], f[MAXN];
$ $ bel[MAXN], pel[MAXN], cln[MAXN];

inline void BuildC($ $ u, $ $ v, $ $ w){
    //printf("DDD %lld %lld %lld\n", u, v, w);
    cnt++; $ $ pre = w, id = 0;
    for(int i = v;i != f[u];i = f[i]){
        cln[i] = pre; pre += pel[i]; bel[i] = id++;
    }
    cln[cnt] = cln[u];
    cln[u] = 0;
    for(int i = v;i != f[u];i = f[i])B(cnt, i, std::min(cln[i], cln[cnt] - cln[i]));
}

void BuildCST($ $ x, $ $ fa){
    dfn[x] = low[x] = ++_time;
    //A(x, [fa]($ $ u, $ $ v, $ $ length){
    for(int i = A.head[x];~i;i = A.next[i]){
        const int u = x, v = A.to[i], length = A.val[i];
        if(i == fa)continue;
        if(dfn[v]){
            low[u] = std::min(low[u], dfn[v]);
        }else{
            f[v] = u; pel[v] = length;
            BuildCST(v, i ^ 1);
            low[u] = std::min(low[u], low[v]);
        }
        if(low[v] > dfn[u])B(u, v, length);
    //});
    }
    //A(x, [fa]($ $ u, $ $ v, $ $ length){
    for(int i = A.head[x];~i;i = A.next[i]){
        const int u = x, v = A.to[i], length = A.val[i];
        if(f[v] != u && dfn[v] > dfn[u]){
            BuildC(u, v, length);
        }
    //});
    }
}

$ $ deep[MAXN], dis[MAXN], pre[MAXN][21];
void DFS($ $ x, $ $ fa){
    //B(x, [x, fa]($ $ u, $ $ v, $ $ length){
    for(int i = B.head[x];~i;i = B.next[i]){
        const int u = x, v = B.to[i], length = B.val[i];
        if(i == fa)continue;
        pre[v][0] = u;
        deep[v] = deep[u] + 1;
        dis[v] = dis[u] + length;
        DFS(v, i ^ 1);
    //});
    }
}
$ $ LCA($ $ x, $ $ y, $ $ &A, $ $ &B) {
    if (deep[x] < deep[y])std::swap(x, y);
    $ $ d = deep[x] - deep[y];
    for(int i = 0; (1 << i) <= d; i++)if (d & (1 << i)) x = pre[x][i];
    if (x == y) return x;
    for(int i = 20; i >= 0; i--)
        if ((1 << i) <= deep[x] && pre[x][i] != pre[y][i]) {
            x = pre[x][i];
            y = pre[y][i];
        }
    A = x; B = y;
    return pre[x][0];
}

int main(){
    scanf("%lld%lld%lld", &n, &m, &q); cnt = n;
    for(int i = 1, u, v, w;i <= m;i++){
        scanf("%d%d%d", &u, &v, &w); A(u, v, w);
    }
    BuildCST(1, -1);
    DFS(1, -1);
    for(int d = 1;d < 21;d++){
        for(int i = 1;i <= cnt;i++){
            pre[i][d] = pre[pre[i][d - 1]][d - 1];
        }
    }
    while(q--){
        $ $ u, v, x, y; scanf("%lld%lld", &u, &v);
        $ $ lca = LCA(u, v, x, y);
        if(lca <= n){
            // circle-point
            // puts("CIRCLEPOINT");
            // printf("%lld %lld %lld\n", dis[u], dis[v], dis[lca]);
            printf("%lld\n", dis[u] + dis[v] - 2 * dis[lca]);
        }else{
            // puts("SQUAREPOINT");
            $ $ ans = dis[u] + dis[v] - dis[x] - dis[y];
            if(bel[x] > bel[y])std::swap(x, y);
            ans += std::min(cln[x] - cln[y] + cln[lca], cln[y] - cln[x]);
            printf("%lld\n", ans);
        }
    }
}