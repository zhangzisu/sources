#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0, f = 0;register char ch = gc();
	while(!isdigit(ch) && (ch ^ 45))ch = gc();
	if(!(ch ^ 45))f = 1, ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#define MAXN 1000010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0, n = $();
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;head[v] = tot++;
}
int vis[MAXN], siv[MAXN << 1], l, r;
void dfs(int x, int fa){
	vis[x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa)continue;
		if(vis[to[i]]){
			l = x;r = to[i];siv[i] = siv[i ^ 1] = 1;
			return;
		}else dfs(to[i], x);
	}
}
long long f[MAXN][2], sb[MAXN];
void dp(int x, int fa){
	vis[x] = 1;
	f[x][0] = f[x][1] = 0;
	if(x != l)f[x][1] = sb[x];
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa || siv[i])continue;
		dp(to[i], x);
		f[x][1] += f[to[i]][0];
		f[x][0] += std::max(f[to[i]][0], f[to[i]][1]);
	}
}
long long ans = 0;
int main(){
	memset(head, -1, sizeof(head));
	for(int i = 1;i <= n;i++)sb[i] = $(), $($(), i);
	for(int i = 1;i <= n;i++){
		if(!vis[i]){
			dfs(i, 0);
			dp(i, 0);
			long long tmp = std::max(f[i][0], f[i][1]);
			std::swap(l, r);
			dp(i, 0);
			tmp = std::max(tmp, std::max(f[i][0], f[i][1]));
			ans += tmp;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
