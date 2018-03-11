#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;
	register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200010
#define INF 0x3F3F3F3F
int head[MAXN], next[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w){
	next[tot] = head[u];to[tot] = v;val[tot] = w;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;val[tot] = w;head[v] = tot++;
}
int n = $(), k = $(), sum, vis[MAXN], f[1000010], size[MAXN], ms[MAXN], root;
int ans = INF, deep[MAXN], dis[MAXN];
void getG(int x, int fa){
	size[x] = 1;ms[x] = 0;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa || vis[to[i]])continue;
		getG(to[i], x);
		ms[x] = std::max(ms[x], size[to[i]]);
		size[x] += size[to[i]];
	}
	ms[x] = std::max(ms[x], sum - size[x]);
	if(ms[x] < ms[root])root = x;
}
void Update(int x, int fa){
	if(dis[x] > k)return;
	ans = std::min(ans, deep[x] + f[k - dis[x]]);
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa || vis[to[i]])continue;
		deep[to[i]] = deep[x] + 1, dis[to[i]] = dis[x] + val[i];
		Update(to[i], x);
	}
}
void Reset(int x, int fa){
	if(dis[x] > k)return;
	f[dis[x]] = INF;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa || vis[to[i]])continue;
		Reset(to[i], x);
	}
}
void Recalc(int x, int fa){
	if(dis[x] > k)return;
	f[dis[x]] = std::min(f[dis[x]], deep[x]);
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa || vis[to[i]])continue;
		Recalc(to[i], x);
	}
}
void slove(int x){
	vis[x] = 1;f[0] = 0;
	for(int i = head[x];~i;i = next[i]){
		if(vis[to[i]])continue;
		deep[to[i]] = 1, dis[to[i]] = val[i];
		Update(to[i], x);
		Recalc(to[i], x);
	}
	for(int i = head[x];~i;i = next[i]){
		if(vis[to[i]])continue;
		Reset(to[i], x);
	}
	for(int i = head[x];~i;i = next[i]){
		if(vis[to[i]])continue;
		sum = size[to[i]];root = n;
		getG(to[i], -1);
		slove(root);
	}
}
int main(){
	memset(head, -1, sizeof(head));
	for(register int i = 1;i < n;i++){
		int $1 = $(), $2 = $();
		$($1, $2, $());
	}
	memset(f, 0x3F, sizeof(f));
	ms[sum = root = n] = INF;
	getG(0, -1);slove(root);
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}
