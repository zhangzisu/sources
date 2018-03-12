#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<algorithm>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
#define MAXM 1000010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;val[tot] = 1;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;val[tot] =-1;head[v] = tot++;
}
int n = $(), m = $(), vis[MAXN], vst[MAXM << 1], dis[MAXN], ans, max, min;
inline int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
void dfs(int x){
	vis[x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(!vis[to[i]]){
			dis[to[i]] = dis[x] + val[i];
			dfs(to[i]);
		}else ans = gcd(ans, std::abs(dis[x] - dis[to[i]] + val[i]));
	}
}
void DFS(int x){
	max = std::max(max, dis[x]);
	min = std::min(min, dis[x]);
	vis[x] = 1; 
	for(int i = head[x];~i;i = next[i]){
		if(vst[i])continue;
		vst[i] = vst[i ^ 1] = 1;
		dis[to[i]] = dis[x] + val[i];
		DFS(to[i]);
	}
}
int main(){
	memset(head, -1 ,sizeof(head));
	while(m--){
		int $1 = $(), $2 = $();
		$($1, $2);
	}
	for(int i = 1;i <= n;i++)if(!vis[i])dfs(i);
	if(ans == 0){
		memset(vis, 0, sizeof(vis));
		for(int i = 1;i <= n;i++)if(!vis[i])max = min = dis[i] = 0, DFS(i), ans += max - min + 1;
		if(ans < 3)return puts("-1 -1"), 0;
		return printf("%d %d\n", ans, 3), 0;
	}
	if(ans < 3)return puts("-1 -1"), 0;
	for(int i = 3;i <= ans;i++)if(!(ans % i))return printf("%d %d\n", ans, i), 0;
	return 0;
}
