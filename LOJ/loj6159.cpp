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
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;head[v] = tot++;
}
#include<map>
using std::map;
inline int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
int n = $(), ans = 0, val[MAXN];
map<int, int> dfs(int x, int fa){
	map<int, int> ret;ret[val[x]] = 1;int tmp;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa)continue;
		auto s = dfs(to[i], x);
		for(auto a : ret)for(auto b : s)if(gcd(a.first, b.first) != 1)ans = std::max(ans, a.second + b.second);
		for(auto b : s)if((tmp = gcd(val[x], b.first)) != 1)ret[tmp] = std::max(ret[tmp], b.second + 1);
	}
	return ret;
}
int main(){
	memset(head, -1, sizeof(head));
	for(int i = 1;i < n;i++)$($(), $());
	for(int i = 1;i <= n;i++)val[i] = $();
	auto x = dfs(1, 0);
	for(auto i : x)ans = std::max(ans, i.second);
	printf("%d\n", ans);
	return 0;
}
