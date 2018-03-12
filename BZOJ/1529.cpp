#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0, f = 0;register char ch = getchar();
	while(!isdigit(ch) && ch ^ 45)ch = getchar();
	if(!(ch ^ 45))f = 1, ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<cstring>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w){
	next[tot] = head[u];to[tot] = v;val[tot] = w;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;val[tot] = w;head[v] = tot++;
}
int n = $(), m = $(), tp[MAXN][2], tc[MAXN], ts[MAXN], vis[MAXN], col[MAXN];
bool dfs(int x){
	vis[x] = 1;
	for(int i = head[x];~i;i = next[i])if(vis[to[i]]){
		if(col[to[i]] == (col[x] ^ val[i]))return 0;
	}else{
		col[to[i]] = !(col[x] ^ val[i]);
		if(!dfs(to[i]))return 0;
	}
	return 1;
}
bool judge(){
	for(int i = 1;i <= m;i++)if(!vis[i] && !dfs(i))return 0;
	return 1;
}
int main(){
	memset(head, -1, sizeof(head));
	for(int i = 1;i <= n;i++)ts[i] = $();
	for(int i = 1;i <= m;i++){
		for(int j = $();j;j--){
			int $1 = $();
			tp[$1][tc[$1]++] = i;
		}
	}
	for(int i = 1;i <= n;i++)$(tp[i][0], tp[i][1], ts[i]);
	puts(judge() ? "YES" : "NO");
	return 0;
}
