#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 200010
#define MAXM 400010
#define MAXT 7000010
int head[MAXN], next[MAXM << 1], to[MAXM << 1], tot;
void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
};
int p[MAXN], dfn[2][MAXN], dfsclk;
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); };
std::vector<int> go[2][MAXN];
void dfs(int x, int d) {
	dfn[d][x] = ++dfsclk;
	for (auto y : go[d][x]) dfs(y, d);
}
int root[MAXN], sum[MAXT], L[MAXT], R[MAXT], cnt;
int add(int n, int l, int r, int p){
	int cur = ++cnt;
	sum[cur] = sum[n] + 1, L[cur] = L[n], R[cur] = R[n];
	if(l == t)return cur;
	int mid = (l + r) >> 1;
	if(p <= mid){
		L[cur] = add(L[n], l, mid, p);
	}else{
		R[cur] = add(R[n], mid + 1, r, p);
	}
	return cur;
}
int query(int n,int m, int l, int r, int L, int R){
	if(l == L && r == R)return sum[n] - sum[m];
	int mid = (l + r) >> 1;
	if(R <= mid)return query(L[n], L[m], l, mid, L, R);
	if(L > mid)return query(R[n], R[m], mid + 1, r, L, R);
	return query(L[n], L[m], l, mid, L, mid)+query(R[n], R[m], mid + 1, r, mid + 1, R);
}
std::vector<int> pos[MAXN];
std::vector<int> check_validity(int n, std::vector<int> x, std::vector<int> y, std::vector<int> s, std::vector<int> e, std::vector<int> l, std::vector<int> r) {
	int m = x.size(), q = s.size();
	tot = 0;
	memset(head, -1, sizeof(head));
	for (int i = 0; i < m; i++) $(x[i], y[i]);
	for (int i = 0; i < n; i++) p[i] = i;
	for (int x = n - 1; x >= 0; x--) {
		for (int i = head[x]; ~i; i = next[i]) {
			if (to[i] < x) continue;
			if (find(to[i]) != find(x)) {
				go[0][x].push_back(find(to[i]));
				p[find(to[i])] = find(x);
			}
		}
	}
	for (int i = 0; i < n; i++) p[i] = i;
	for (int x = 0; x < n; x++) {
		for (int i = head[x]; ~i; i = next[i]) {
			if (to[i] > x) continue;
			if (find(to[i]) != find(x)) {
				go[1][x].push_back(to[i]);
				p[find(to[i])] = find(x);
			}
		}
	}
	dfsclk = 0, dfs(1, 0);
	dfsclk = 0, dfs(1, 1);
	for (int i = 0; i < n; i++) go[0][i].clear(), go[1][i].clear();
	cnt = 0;
	for(int i = 0;i < n;i++)root[i] = add(1, 1, n, )
	for (int i = 0; i < n; i++)pos[i].clear();
}
int main() {
	//
	return 0;
}