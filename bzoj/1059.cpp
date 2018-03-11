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
#define MAXN 400
int head[MAXN], next[MAXN * MAXN], to[MAXN * MAXN], tot;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
int vis[MAXN], match[MAXN], timer;
inline bool $(int x){
	for(int i = head[x];~i;i = next[i]){
		if(vis[to[i]] == timer)continue;
		vis[to[i]] = timer;
		if(!~match[to[i]] || $(match[to[i]]))return match[to[i]] = x, 1;
	}
	return 0;
}
int main(){
	register int _ = $();
	while(_--){
		register int n = $();
		memset(head, -1, sizeof(head));tot = 0;
		memset(match, -1, sizeof(match));
		memset(vis, 0, sizeof(vis)); 
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				if($())$(i, j);
			}
		}
		for(timer = 1;timer <= n;timer++)if(!$(timer)){puts("No");goto fail;};
		puts("Yes");
		fail:;
	}
	return 0;
}
