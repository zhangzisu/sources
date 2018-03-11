#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1010
#define MAXM 5010
int head[MAXN], to[MAXM << 1], val[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v, int w){
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, m, q, w[MAXN], min = 0x7FFFFFFF, max = 0;

int dfn[MAXN], low[MAXN], ins[MAXN], idx;
int stk[MAXN], dcc[MAXN], cnt, top;

inline void Tarjin(int x, int w, int fa) {
    dfn[x] = low[x] = idx++;
    ins[stk[++top] = x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if(val[i] > w)continue;
        if (i == (fa ^ 1)) continue;
        if (dfn[to[i]]) {
            if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            Tarjin(to[i], w, i);
            low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (low[x] == dfn[x]) {
        ++cnt;
        do {
            dcc[stk[top]] = cnt;
            ins[stk[top]] = 0;
        } while (stk[top--] != x);
        cnt++;
    }
}

inline bool judge(int u, int v, int w){
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(ins, 0, sizeof(ins));
    memset(dcc, 0, sizeof(dcc));
    idx = cnt = top = 0;
    if(!dfn[u])Tarjin(u, w, -1);
    if(!dfn[v])return 0;
    return dcc[u] == dcc[v];
}

int main(){
    scanf("%d%d%d", &n, &m, &q); memset(head, -1, sizeof(head));
    for(int i = 1;i <= n;i++)scanf("%d", &w[i]);
    for(int i = 1;i <= m;i++){
        int u, v; scanf("%d%d", &u, &v);
        $(u, v, std::abs(w[u] - w[v]));
        min = std::min(min, std::abs(w[u] - w[v]));
        max = std::max(max, std::abs(w[u] - w[v]));
    }
    for(int i = 1;i <= q;i++){
        int u, v; scanf("%d%d", &u, &v);
        register int l = min, r = max, ans = -1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(judge(u, v, mid))ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        if(!~ans)puts("infinitely");
        else printf("%d\n", ans);
    }
    return 0;
}