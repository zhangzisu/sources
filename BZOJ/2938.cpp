#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 300010
int son[MAXN][2], fail[MAXN], fuck[MAXN], cnt = 1;
inline void insert(const char *s){
    int p = 1;
    for(int i = 0;s[i];i++){
        int next = s[i] - '0';
        if(!son[p][next])son[p][next] = ++cnt;
        p = son[p][next];
    }
    fuck[p] = 1;
}
std::queue<int> Q;
inline void build(){
    son[0][0] = son[0][1] = 1;
    Q.push(1);
    while(Q.size()){
        int x = Q.front(); Q.pop();
        for(int i = 0;i < 2;i++){
            int &s = son[x][i];
            if(!s)s = son[fail[x]][i];
            else fail[s] = son[fail[x]][i], Q.push(s);
        }
    }
}
int vis[MAXN], ins[MAXN];
inline void dfs(int x){
    if(vis[x] && ins[x])puts("TAK"), exit(0);
    if(vis[x])return;
    vis[x] = ins[x] = 1;
    // printf("VIS : %d\n", x);
    if(!fuck[son[x][0]])dfs(son[x][0]);
    if(!fuck[son[x][1]])dfs(son[x][1]);
    ins[x] = 0;
}
int n;
char buf[MAXN];
int main(){
    scanf("%d", &n);
    for(int i = 1;i <= n;i++){
        scanf("%s", buf);
        insert(buf);
    }
    build();
    // for(int i = 1;i <= cnt;i++)printf("node %d : lson = %d, rson = %d\n", i, son[i][0], son[i][1]);
    dfs(1);
    puts("NIE");
    return 0;
}