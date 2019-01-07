#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 500010
#define INF 0x3F3F3F3F
std::vector<int> next[MAXN];
int n, sum[MAXN], size[MAXN], deep[MAXN], in[MAXN], out[MAXN];
int prf[MAXN], ans[MAXN], pos[MAXN], dfsclk;
int f[1 << 22];
char buf[3];
void dfs(int x) {
	size[x] = 1;
	for (auto y : next[x]) {
		sum[y] ^= sum[x];
		deep[y] = deep[x] + 1;
		dfs(y);
		size[x] += size[y];
	}
}
void fsd(int x) {
	pos[in[x] = ++dfsclk] = x;
	for (auto y : next[x])
		if (size[y] > size[prf[x]]) prf[x] = y;
	if (prf[x]) fsd(prf[x]);
	for (auto y : next[x])
		if (y != prf[x]) fsd(y);
	out[x] = dfsclk;
}
void sdf(int x) {
	for (auto y : next[x]) {
		if (y == prf[x]) continue;
		sdf(y);
		for (int i = in [y]; i <= out[y]; i++) f[sum[pos[i]]] = -INF;
		ans[x] = std::max(ans[x], ans[y]);
	}
	if (prf[x]) {
		sdf(prf[x]);
		ans[x] = std::max(ans[x], ans[prf[x]]);
		ans[x] = std::max(ans[x], f[sum[x]] - deep[x]);
		for (int d = 0; d < 22; d++) ans[x] = std::max(ans[x], f[sum[x] ^ (1 << d)] - deep[x]);
	}
	f[sum[x]] = std::max(f[sum[x]], deep[x]);
	for (auto y : next[x]) {
		if (y == prf[x]) continue;
		for (int i, _i = in [y]; _i <= out[y]; _i++) {
			i = pos[_i];
			ans[x] = std::max(ans[x], deep[i] + f[sum[i]] - 2 * deep[x]);
			for (int d = 0; d < 22; d++) ans[x] = std::max(ans[x], f[sum[i] ^ (1 << d)] + deep[i] - 2 * deep[x]);
		}
		for (int i, _i = in [y]; _i <= out[y]; _i++) {
			i = pos[_i];
			f[sum[i]] = std::max(f[sum[i]], deep[i]);
		}
	}
}
int main() {
	scanf("%d", &n);
	std::fill(f, f + (1 << 22), -INF);
	for (int i = 2, p; i <= n; i++) {
		scanf("%d%s", &p, buf);
		next[p].push_back(i);
		sum[i] = 1 << (buf[0] - 'a');
	}
	dfs(1), fsd(1), sdf(1);
	for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}