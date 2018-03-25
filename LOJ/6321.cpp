#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 100010
int n, s, k;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v){
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int g[MAXN][30], f[MAXN][30];
void dp(int x, int fa){
    for(int i = head[x];~i;i = next[i]){
        if(to[i] == fa)continue;
        for(int d = 1;d <= k;d++)g[x][d] += g[to[i]][d - 1];
        for(int d = 0;d < k;d++)f[x][d] += f[]
    }
}
int main(){
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &s, &k);
    for(int i = 1, x, y;i < n;i++){
        scanf("%d%d%d", &x, &y);
        $(x, y);
    }
    $(fa[1][0] = 1);
    for(int d = 1;d < 18;d++){
        for(int i = 1;i <= n;i++){
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
        }
    }
    int l = 0, r = n / s + 1, ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid))ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}