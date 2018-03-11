#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 5000050
int son[MAXN][2], cnt = 1;
char buf[MAXN];
inline void insert(const char *s){
    int pos = 1;
    for(int i = 0;s[i];i++){
        if(!son[pos][s[i] ^ 48])son[pos][s[i] ^ 48] = ++cnt;
        pos = cnt;
    }
}
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
int main(){
    scanf("%d%d", &n, &m);
    
    return 0;
}