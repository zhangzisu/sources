#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1010
int n = $(), m = $(), ans = 0;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
int match[MAXN], vis[MAXN];
inline bool $(int x){
	for(int i = head[x];~i;i = next[i]){
		if(vis[to[i]])continue;vis[to[i]] = 1;
		if(!~match[to[i]] || $(match[to[i]])){
			match[to[i]] = x;
			return 1;
		}
	}
	return 0;
}
int main(){
	memset(head, -1, sizeof(head));
	memset(match, -1, sizeof(match));
	for(int i = 1;i <= m;i++)$(i, $()), $(i, $());
	for(int i = 1;i <= m;i++){
		memset(vis, 0, sizeof(vis));
		if($(i))ans++;else break;
	}
	printf("%d\n", ans);
	return 0;
}
