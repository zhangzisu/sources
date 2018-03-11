#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 610
#define MAXM 300010
int head[MAXN], to[MAXM], next[MAXM], tot = 0, ans;
inline void $(int u, int v){next[tot]  = head[u], to[tot] = v, head[u] = tot++;}
int n = $(), k1 = $(), k2 = $();
int dfn[MAXN], low[MAXN], ins[MAXN], stk[MAXN], bel[MAXN], vis[MAXN], f[MAXN][MAXN], top, tim, scc;
void Tarjin(int x){
	dfn[x] = low[x] = ++tim;ins[stk[++top] = x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(dfn[to[i]]){if(ins[to[i]])low[x] = std::min(low[x], dfn[to[i]]);}
		else{Tarjin(to[i]);low[x] = std::min(low[x], low[to[i]]);}
	}
	if(dfn[x] == low[x]){++scc;do{ins[stk[top]] = 0;bel[stk[top]] = scc;}while(stk[top--] != x);}
}
int main(){
	memset(head, -1, sizeof(head));memset(f, 0x3F, sizeof(f));
	for(int i = 1;i <= n;i++)f[i][i] = 0;
	while(k1--){int a = $(), b = $();$(a, b);f[a][b] = std::min(f[a][b], 1);$(b, a);f[b][a] = std::min(f[b][a], -1);}
	while(k2--){int a = $(), b = $();$(b, a);f[b][a] = std::min(f[b][a], 0);}
	for(int i = 1;i <= n;i++)if(!dfn[i])Tarjin(i);
	for(int i = 1;i <= n;i++)if(f[i][i] == -1)return puts("NIE"), 0;
	for(int k = 1;k <= n;k++)for(int i = 1;i <= n;i++)for(int j = 1;j <= n;j++)
		f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
	for(int i = 1;i <= scc;i++){
		int res = 0;
		for(int j = 1;j <= n;j++)if(bel[j] == i)
			for(int k = 1;k <= n;k++)if(bel[k] == i)res = std::max(res, f[j][k]);
		ans += res + 1;
	}
	for(int i = 1;i <= n;i++)if(f[i][i])return puts("NIE"), 0;
	return printf("%d\n", ans), 0;
}
