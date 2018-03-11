#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 100010
int t, n, f[MAXN], g[MAXN];
std::vector<int> V[MAXN], ans;
int col[MAXN];
void DFS(int x){
    if(V[x].empty())return;
    int cnt[3] = {0, 0, 0};
    for(auto y : V[x]) DFS(y), cnt[col[y]]++;
    if((cnt[0] & 1) + cnt[1] < cnt[2])col[x] = 2;
    if((cnt[0] & 1) + cnt[2] < cnt[1])col[x] = 1;
}
void fill(int x){
    if(V[x].empty())return g[x] = (col[x] == 0), void();
    for(auto i : V[x])fill(i);
}
void fr(int);
void fb(int);
void fr(int x){
    if(col[x] == 1)return fill(x);
    if(col[x] == 2)return;
    if(V[x].empty())return g[x] = 1, void();
    for(auto i : V[x]){
        if(col[i] == 0)fr(i);
        if(col[i] == 2)fb(i);
    }
}
void fb(int x){
    if(V[x].empty())return;
    int cnt[3] = {0, 0, 0};
    for(auto y : V[x]) cnt[col[y]]++;
    if(cnt[0] & 1 || cnt[2] != cnt[1] + 1)return;
    for(auto y : V[x]){
        if(col[y] == 2)fb(y);
        if(col[y] == 0)fr(y);
    }
}
int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        memset(col, 0, sizeof(col));
        memset(g, 0, sizeof(g));
        ans.clear();
        for(int i = 1;i <= n;i++)V[i].clear();
        for(int i = 1, x;i <= n;i++){
            scanf("%d", &x); if(x)V[x].push_back(i);
        }
        for(int i = 1;i <= n;i++){
            scanf("%d", &col[i]); col[i]++;
        }
        DFS(1);
        // puts("DBG");
        // for(int i = 1;i <= n;i++)printf("%d ", col[i]);
        // puts("");
        if(col[1] == 2) { puts("-1"); continue; }
        fr(1);
        for(int i = 1;i <= n;i++)if(g[i])ans.push_back(i);
        printf("%lu ", ans.size());
        for(auto i : ans)printf("%d ", i);
        puts("");
    }
    return 0;
}