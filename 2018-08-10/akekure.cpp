#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MOD 1000000007
#define MAXN 200010
inline void up(int &x, int y){
	if((x += y) >= MOD) x -= MOD;
}
int n, m, k, res, u[MAXN], v[MAXN], p[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int c[MAXN], f[MAXN][2];
void dfs(int x, int fa){
	f[x][0] = f[x][1] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if(to[i] == fa) continue;
		dfs(to[i], x);
		f[x][0] = 1LL * f[x][0] * (f[to[i]][0] + f[to[i]][1]) % MOD;
		f[x][1] = 1LL * f[x][1] * f[to[i]][0] % MOD;
	}
	if(c[x]) f[x][0] = 0;
}
int main(){
	freopen("akekure.in", "r", stdin);
	freopen("akekure.out", "w", stdout);
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int u, v, i = 1; i <= m; i++) {
		scanf("%d%d", &u, &v);
		if (find(u) == find(v)) {
			::u[k] = u;
			::v[k] = v;
			k++;
//			fprintf(stderr, "OPT EDGE: %d-%d\n", u, v);
		} else {
			$(u, v);
			p[find(u)] = v;
//			fprintf(stderr, "ADD EDGE: %d-%d\n", u, v);
		}
	}
	for(int d = 0;d < (1 << k);d++){
		memset(f, 0, sizeof(f));
		memset(c, 0, sizeof(c));
		for(int i = 0;i < k;i++)
			if((d >> i) & 1)
				c[u[i]] = c[v[i]] = 1;
		dfs(1, 0);
//		printf("stat: %d, ret: %d\n", d, f[1][0] + f[1][1]);
		res = (res + ((__builtin_popcount(d) & 1) ? -1LL : 1LL) * (f[1][0] + f[1][1]) % MOD) % MOD;
		if(res < 0)res += MOD;
		if(res >= MOD)res -= MOD;
	}
	printf("%d\n", res);
	return 0;
}
