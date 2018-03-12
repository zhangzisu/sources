#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define BUF 65536
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $() {
	register int x = 0, f = 0; register char ch = gc();
	while (!isdigit(ch) && (ch ^ 45))ch = gc();
	if (!(ch ^ 45))f = 1, ch = gc();
	for (; isdigit(ch); ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#define MAXN 5010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0, n = $();
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;head[v] = tot++;
}
long long f1[MAXN], f2[MAXN], f[MAXN], ans;
void dfs(int x, int fa, int d){
	f[d]++;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa)continue;
		dfs(to[i], x, d + 1);
	}
}
int main(){
	memset(head, -1, sizeof(head));
	for(int i = 1;i < n;i++)$($(), $());
	for(int x = 1;x <= n;x++){
		memset(f1, 0, sizeof(int) * n + 32);
		memset(f2, 0, sizeof(int) * n + 32);
		for(int i = head[x];~i;i = next[i]){
			memset(f, 0, sizeof(int) * n + 32);
			dfs(to[i], x, 1);
			for(int i = 1;i <= n;i++){
				ans += f2[i] * f[i];
				f2[i] += f1[i] * f[i];
				f1[i] += f[i];
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
