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
#define MAXN 100010
#define INF 123456789123456789LL
int head[MAXN], next[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w){
	next[tot] = head[u];to[tot] = v;val[tot] = w;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;val[tot] = w;head[v] = tot++;
}
int top[MAXN], dfn[MAXN], fa[MAXN], pos[MAXN], size[MAXN], tim, n = $(), m = $();
long long deep[MAXN];
void gs(int x){
	size[x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(fa[x] == to[i])continue;
		fa[to[i]] = x;deep[to[i]] = deep[x] + val[i];
		gs(to[i]);size[x] += size[to[i]];
	}
}
void sp(int x){
	pos[dfn[x] = ++tim] = x;if(!~top[x])top[x] = x;
	int huge = 0;
	for(int i = head[x];~i;i = next[i])if(to[i] != fa[x] && size[to[i]] > size[huge])huge = to[i];
	if(huge)top[huge] = top[x], sp(huge);
	for(int i = head[x];~i;i = next[i])if(to[i] != fa[x] && to[i] != huge)sp(to[i]);
}
bool t[MAXN << 2];
long long k[MAXN << 2], b[MAXN << 2], min[MAXN << 2];
inline long long g(long long k, long long b, long long x){
	return k * x + b;
}
inline void pushUp(int n, int l, int r){
	if(l != r)min[n] = std::min(min[n << 1], min[n << 1 | 1]);
	if(t[n])min[n] = std::min(min[n], std::min(g(k[n], b[n], deep[pos[l]]), g(k[n], b[n], deep[pos[r]])));
}
void Build(int n, int l, int r){
	min[n] = INF;
	if(l == r)return;
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid);
	Build(n << 1 | 1, mid + 1, r);
}
inline void pushDown(int n, int l, int r, long long K, long long B){
	if(!t[n]){k[n] = K;b[n] = B;t[n] = 1;pushUp(n, l, r);return;}
	long long $1 = g(k[n], b[n], deep[pos[l]]), $2 = g(k[n], b[n], deep[pos[r]]);
	long long $3 = g(K, B, deep[pos[l]]), $4 = g(K, B, deep[pos[r]]);
	if($1 <= $3 && $2 <= $4)return;
	if($1 >= $3 && $2 >= $4){k[n] = K;b[n] = B;pushUp(n, l, r);return;}
	int mid = (l + r) >> 1;
	if($1 > $3){
		if((b[n] - B) <= (K - k[n]) * deep[pos[mid]])pushDown(n << 1, l, mid, K, B);
		else std::swap(K, k[n]), std::swap(B, b[n]), pushDown(n << 1 | 1, mid + 1, r, K, B);
	}else{
		if((B - b[n]) > (k[n] - K) * deep[pos[mid]])pushDown(n << 1 | 1, mid + 1, r, K, B);
		else std::swap(K, k[n]), std::swap(B, b[n]), pushDown(n << 1, l, mid, K, B);
	}
	pushUp(n, l, r);
}
void Modify(int n, int l, int r, int L, int R, long long K, long long B){
	if(l == L && r == R){
		pushDown(n, l, r, K, B);
		return;
	}
	int mid = (l + r) >> 1;
	if(R <= mid)Modify(n << 1, l, mid, L, R, K, B);
	else if(L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, K, B);
	else Modify(n << 1, l, mid, L, mid, K, B), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, K, B);
	pushUp(n, l, r);
}
long long Query(int n, int l, int r, int L, int R){
	if(l == L && r == R)return min[n];
	long long ret = t[n] ? std::min(g(k[n], b[n], deep[pos[L]]), g(k[n], b[n], deep[pos[R]])) : INF;
	int mid = (l + r) >> 1;
	if(R <= mid)ret = std::min(ret, Query(n << 1, l, mid, L, R));
	else if(L > mid)ret = std::min(ret, Query(n << 1 | 1, mid + 1, r, L, R));
	else ret = std::min(ret, std::min(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R)));
	return ret;
}
long long Query(int n, int l, int r, int p){
	if(l == r)return min[n];
	int mid = (l + r) >> 1;
	long long ret = !t[n] ? INF : g(k[n], b[n], deep[pos[p]]);
	if(p <= mid)return std::min(ret, Query(n << 1, l, mid, p));
	else return std::min(ret, Query(n << 1 | 1, mid + 1, r, p));
}
inline int $(int u, int v){
	for(;top[u] != top[v];u = fa[top[u]])if(deep[top[u]] < deep[top[v]])std::swap(u, v);
	return deep[u] > deep[v] ? v : u;
}
inline void Add(){
	int o, s = (o = $()), t = $(), lca = $(s, t);
	long long x = $(), y = $();
	long long k = -x, b = x * deep[s] + y;
	for(;top[s] != top[lca];s = fa[top[s]])Modify(1, 1, n, dfn[top[s]], dfn[s], k, b);
	Modify(1, 1, n, dfn[lca], dfn[s], k, b);
	k = x;b = x * deep[o] - 2 * x * deep[lca] + y;
	for(;top[t] != top[lca];t = fa[top[t]])Modify(1, 1, n, dfn[top[t]], dfn[t], k, b);
	Modify(1, 1, n, dfn[lca], dfn[t], k, b);
}
inline void Qry(){
	int s = $(), t = $();
	long long ans = INF;
	for(;top[s] != top[t];s = fa[top[s]]){
		if(deep[top[s]] < deep[top[t]])std::swap(s, t);
		ans = std::min(ans, Query(1, 1, n, dfn[top[s]], dfn[s]));
	}
	if(deep[s] < deep[t])std::swap(s, t);
	ans = std::min(ans, Query(1, 1, n, dfn[t], dfn[s]));
	printf("%lld\n", ans);
}
int main(){
	memset(head, -1, sizeof(head));
	memset(top, -1, sizeof(top));
	for(int i = 1;i < n;i++){
		register int $1 = $(), $2 = $();
		$($1, $2, $());
	}
	gs(1);sp(1);Build(1, 1, n);
	while(m--){
		if($() & 1)Add();
		else Qry();
	}
	return 0;
}
