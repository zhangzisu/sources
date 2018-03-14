#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 200010
#define INF 0x3F3F3F3F
#define MOD 1000000007
long long head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(long long u, long long v){
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
long long fa[MAXN], bfn[MAXN], pos[MAXN], bfsclk;
std::queue<long long> Q;
inline void BFS(){
	Q.push(1);
	while(Q.size()){
		long long x = Q.front(); Q.pop();
		pos[bfn[x] = ++bfsclk] = x;
		for(long long i = head[x]; ~i; i = next[i]){
			if(to[i] == fa[x])continue;
			fa[to[i]] = x;
			Q.push(to[i]);
		}
	}
}

long long first[MAXN], last[MAXN];
inline void DFS(long long x){
	first[x] = INF; last[x] = 0;
	for(long long i = head[x];~i;i = next[i]){
		if(to[i] == fa[x])continue;
		first[x] = std::min(first[x], bfn[to[i]]);
		last[x] = std::max(last[x], bfn[to[i]]);
		DFS(to[i]);
	}
}

struct tag{
	long long k, b;
	inline tag(long long k = 0, long long b = 0):k(k), b(b) { }
}tags[MAXN << 2];
long long sum[MAXN << 2];
inline void tagAdd(tag& x, tag y){
	x.k = x.k * y.k % MOD;
	x.b = (y.k * x.b % MOD + y.b) % MOD;
}

inline long long pushDown(long long n, long long l, long long r){
	const long long L = n << 1;
	const long long R = n << 1 | 1;
	const long long mid = (l + r) >> 1;
	if(tags[n].k || tags[n].b){
		sum[L] = (tags[n].k * sum[L] + tags[n].b * (mid - l + 1)) % MOD;
		sum[R] = (tags[n].k * sum[R] + tags[n].b * (r - mid)) % MOD;
		tagAdd(tags[L], tags[n]);
		tagAdd(tags[R], tags[n]);
		tags[n] = tag(0, 0);
	}
	return mid;
}

inline void add(long long n, long long l, long long r, long long L, long long R, long long k, long long b){
	if(l == L && r == R){
		sum[n] = (1LL * k * sum[n] + 1LL * (r - l + 1) * b) % MOD;
		tagAdd(tags[n], tag(k, b));
		return;
	}
	long long mid = pushDown(n, l, r);
	if(R <= mid)add(n << 1, l, mid, L, R, k, b);
	else if(L > mid)add(n << 1 | 1, mid + 1, r, L, R, k, b);
	else add(n << 1, l, mid, L, mid, k, b), add(n << 1 | 1, mid + 1, r, mid + 1, R, k, b);
	sum[n] = (sum[n << 1] + sum[n << 1 | 1]) % MOD;
}

inline long long qry(long long n, long long l, long long r, long long L, long long R){
	if(l == L && r == R)return sum[n];
	long long mid = pushDown(n, l, r);
	if(R <= mid)return qry(n << 1, l, mid, L, R);
	if(L > mid)return qry(n << 1 | 1, mid + 1, r, L, R);
	return (qry(n << 1, l, mid, L, mid) + qry(n << 1 | 1, mid + 1, r, mid + 1, R)) % MOD;
}

long long n, m;
int main(){
	#ifndef DEBUG
	freopen("ruby.in" , "r", stdin );
	freopen("ruby.out", "w", stdout);
	#endif
	scanf("%lld%lld", &n, &m);
	memset(head, -1, sizeof(head));
	for(long long i = 1;i < n;i++){
		long long x, y; scanf("%lld%lld", &x, &y);
		$(x, y);
	}
	BFS(); DFS(1);
	while(m--){
		long long x, k, b; scanf("%lld%lld%lld", &x, &k, &b);
		long long L = first[x], R = last[x];
		long long ans = 0;
		if(R){
			add(1, 1, n, L, R, k, b);
			(ans += qry(1, 1, n, L, R)) %= MOD;
		}
		if(fa[x]){
			add(1, 1, n, bfn[fa[x]], bfn[fa[x]], k, b);
			(ans += qry(1, 1, n, bfn[fa[x]], bfn[fa[x]])) %= MOD;
		}
		add(1, 1, n, bfn[x], bfn[x], k, b);
		(ans += qry(1, 1, n, bfn[x], bfn[x]));
		printf("%lld\n", ans);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
