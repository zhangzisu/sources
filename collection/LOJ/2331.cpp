#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1010
#define MOD 998244353
const int INF = (~0U) >> 1;
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int T, n, q, a;
std::vector<int> V;
struct operation_t {
	int l, r, w;
} op[MAXN];
int f[MAXN][MAXN], t[MAXN], l[MAXN], max[MAXN];
inline void up(int& x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int cao(int w) {
	int k = 0;
	for (int i = 0; i < (int)V.size() - 1; i++)
		if (max[i] == w) t[++k] = i;
	memset(l, 0, sizeof(l));
	for (int i = 1; i <= q; i++) {
		if (op[i].w == w) {
			if (!k) return 0;
			int l = std::lower_bound(t + 1, t + k + 1, op[i].l) - t;
			int r = std::lower_bound(t + 1, t + k + 1, op[i].r) - t - 1;
			::l[r] = std::max(::l[r], l);
		}
	}
	memset(f[0], 0, sizeof(f[0]));
	f[0][0] = 1;
	for (int i = 1; i <= k; i++) {
		memset(f[i], 0, sizeof(f[i]));
		int all = fuck(w, V[t[i] + 1] - V[t[i]]);
		int exc = fuck(w - 1, V[t[i] + 1] - V[t[i]]);
		for (int j = 0; j < i; j++) {
			if (j >= l[i]) up(f[i][j], 1LL * f[i - 1][j] * exc % MOD);
			up(f[i][i], 1LL * f[i - 1][j] * (all - exc + MOD) % MOD);
		}
	}
	int ret = 0;
	for (int i = 0; i <= k; i++) up(ret, f[k][i]);
	return ret;
}
int main() {
	for (scanf("%d", &T); T; T--) {
		scanf("%d%d%d", &n, &q, &a);
		memset(f, 0, sizeof(f));
		memset(t, 0, sizeof(t));
		memset(l, 0, sizeof(l));
		memset(max, 0, sizeof(max));
		memset(op, 0, sizeof(op));
		V.clear();
		for (int i = 1; i <= q; i++) {
			scanf("%d%d%d", &op[i].l, &op[i].r, &op[i].w);
			op[i].r++;
			V.push_back(op[i].l);
			V.push_back(op[i].r);
		}
		V.push_back(1);
		V.push_back(n + 1);
		std::sort(V.begin(), V.end());
		V.erase(std::unique(V.begin(), V.end()), V.end());
		std::fill(max, max + V.size(), INF);
		for (int i = 1; i <= q; i++) {
			op[i].l = std::lower_bound(V.begin(), V.end(), op[i].l) - V.begin();
			op[i].r = std::lower_bound(V.begin(), V.end(), op[i].r) - V.begin();
			for (int j = op[i].l; j < op[i].r; j++) max[j] = std::min(max[j], op[i].w);
		}
		std::sort(op + 1, op + q + 1, [](const operation_t& a, const operation_t& b) { return a.w < b.w; });
		int ans = 1;
		for (int i = 1; i <= q; i++) {
			if (op[i].w == op[i + 1].w) continue;
			ans = 1LL * ans * cao(op[i].w) % MOD;
		}
		for (int i = 0; i < (int)V.size() - 1; i++)
			if (max[i] == INF) ans = 1LL * ans * fuck(a, V[i + 1] - V[i]) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}