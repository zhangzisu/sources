#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 1010
#define MAXM 200010
int n, m, k, p[MAXN], ans = 0;
struct edge{int u, v, w;inline friend bool operator < (const edge &a, const edge &b){return a.w < b.w;}}e[MAXM];
bool fucked[MAXN];
inline int find(int x){return x == p[x] ? x : p[x] = find(p[x]);}
int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1, j, k, l;i <= m;i++){
        scanf("%d%d%d", &j, &k, &l);
        e[i] = {j, k, l};
    }
    std::sort(e + 1, e + 1 + m);
    for(int i = 1;i <= n;i++)p[i] = i;
    for(int i = 1;i <= m;i++){
        int U = find(e[i].u), V = find(e[i].v);
        if(U == V)continue;
        if(e[i].u == 0 || e[i].v == 0){
            if(!k)continue;
            k--;
        }
        p[U] = V;
        ans += e[i].w;
    }
    printf("%d\n", ans);
    return 0;
}