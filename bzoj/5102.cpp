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
int head[MAXN], to[MAXN << 2], next[MAXN << 2], tot = 0, ans;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;head[v] = tot++;
}
int fa[MAXN], dfn[MAXN], low[MAXN], deep[MAXN], tim, n = $(), m = $();
int f[MAXN], g[MAXN], Q[MAXN], H, T;
inline void calc(int root, int x){
	int n = deep[x] - deep[root] + 1;
	for(int j = n, p = x;j;j--, p = fa[p])g[j] = f[p];
	for(int i = 1;i <= n;i++)g[i + n] = g[i];
	Q[H = T = 0] = 1;
	for(int i = 2;i <= n + (n >> 1);i++){
		while(H <= T && i - Q[H] > (n >> 1))H++;
		ans = std::max(ans, g[Q[H]] + g[i] + i - Q[H]);
		while(H <= T && g[Q[T]] - Q[T] < g[i] - i)T--;
		Q[++T] = i;
	}
	for(int i = 2;i <= n;i++)f[root] = std::max(f[root], g[i] + std::min(i - 1, n - i + 1));
}
void Tarjin(int x){
	dfn[x] = low[x] = ++tim;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa[x])continue;
		if(!dfn[to[i]])fa[to[i]] = x, deep[to[i]] = deep[x] + 1, Tarjin(to[i]);
		low[x] = std::min(low[x], low[to[i]]);
		if(low[to[i]] > dfn[x]){
			ans = std::max(ans, f[x] + f[to[i]] + 1);
			f[x] = std::max(f[x], f[to[i]] + 1);
		}
	}
	for(int i = head[x];~i;i = next[i])if(fa[to[i]] != x && dfn[to[i]] > dfn[x])calc(x, to[i]);
}
int main(){
	memset(head, -1, sizeof(head));
	while(m--){
		register int n = $() - 1, a = $(), b;
		while(n--){
			b = $();
			$(a, b);
			a = b;
		}
	}
	Tarjin(1);printf("%d\n", ans);
	return 0;
}
