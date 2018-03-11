#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 30010
#define MAXM 50010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], len[MAXN << 1], tot = 0;
inline void $(int u, int v, int w){
	next[tot] = head[u];to[tot] = v;len[tot] = w;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;len[tot] = w;head[v] = tot++;
}
int u[MAXM], v[MAXM], w[MAXM], id[MAXM], _[MAXN], n = $(), m = $();
inline int find(int x){return x == _[x] ? x : _[x] = find(_[x]);}
inline int cmp(const int &a, const int &b){return w[a] < w[b];}
int val[MAXN], fa[MAXN], deep[MAXN], size[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], tim;
void s(int x){
	size[x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa[x])continue;
		fa[to[i]] = x;deep[to[i]] = deep[x] + 1;val[to[i]] = len[i];
		s(to[i]);size[x] += size[to[i]];
	}
}
void p(int x){
	int huge = 0;pos[dfn[x] = ++tim] = x;
	if(!top[x])top[x] = x;
	for(int i = head[x];~i;i = next[i])
		if(to[i] != fa[x] && size[to[i]] > size[huge])huge = to[i];
	if(huge){top[huge] = top[x];p(huge);}
	for(int i = head[x];~i;i = next[i])
		if(to[i] != fa[x] && to[i] != huge)p(to[i]);
}
int max[MAXN << 2];
inline void pushUp(int x){max[x] = std::max(max[x << 1], max[x << 1 | 1]);}
void Build(int n, int l, int r){
	if(l == r){max[n] = val[pos[l]];return;}
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid);Build(n << 1 | 1, mid + 1, r);
	pushUp(n);
}
int Query(int n, int l, int r, int L, int R){
	if(l == L && r == R)return max[n];
	int mid = (l + r) >> 1;
	if(R <= mid)return Query(n << 1, l, mid, L, R);
	else if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R);
	else return std::max(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
inline int LCA(int u, int v){
	while(top[u] != top[v]){
		if(deep[top[u]] < deep[top[v]])std::swap(u, v);
		u = fa[top[u]];
	}
	return deep[u] < deep[v] ? u : v;
}
int main(){
	memset(head, -1, sizeof(head));
	for(int i = 1;i <= n;i++)_[i] = i;
	for(int i = 1;i <= m;i++){
		u[i] = $();v[i] = $();w[i] = $();id[i] = i;
	}
	std::sort(id + 1, id + m + 1, cmp);
	for(int i = 1;i <= m;i++){
		int U = find(u[id[i]]), V = find(v[id[i]]);
		if(U == V)continue;
		$(u[id[i]], v[id[i]], w[id[i]]);
		_[U] = V;
	}
	for(int i = 1;i <= n;i++)if(!size[i])s(i), p(i);
	Build(1, 1, tim);
	register int q = $();
	while(q--){
		register int u = $(), v = $(), ans = 0;
		if(find(u) != find(v)){puts("-1");continue;}
		int lca = LCA(u, v);
		while(top[u] != top[lca]){
			ans = std::max(ans, Query(1, 1, n, dfn[top[u]], dfn[u]));
			u = fa[top[u]];
		}
		if(u != lca)ans = std::max(ans, Query(1, 1, n, dfn[lca] + 1, dfn[u]));
		while(top[v] != top[lca]){
			ans = std::max(ans, Query(1, 1, n, dfn[top[v]], dfn[v]));
			v = fa[top[v]];
		}
		if(v != lca)ans = std::max(ans, Query(1, 1, n, dfn[lca] + 1, dfn[v]));
		printf("%d\n", ans);
	}
	return 0;
}
