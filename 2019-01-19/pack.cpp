#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 20
#define MAXM 300010
int n, m, k, D[MAXN], I[MAXN], M[MAXN], S[MAXN], ans[MAXM];
inline int calc(int d, int i, int t) { return t < d ? 0 : (t - d) / i + 1; }
int wtf[256];
struct query_t {
	int d, s, id;
} q[MAXM];
int can[MAXM];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d%d%d", D + i, I + i, M + i, S + i);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) scanf("%d%d", &q[i].d, &q[i].s), q[i].id = i, k = std::max(k, q[i].s);
	for (int i = 0; i < n; i++) M[i] = std::min(M[i], k / S[i]);
	std::sort(q, q + m, [](query_t a, query_t b) { return a.d < b.d; });
	can[0] = 1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int delta = std::min(M[j], calc(D[j], I[j], q[i].d) - calc(D[j], I[j], q[i - 1].d));
			if (delta) {
				for (int t = 0; t < delta; t++) {
					for (int p = k - S[j]; p >= 0; p--) can[p + S[j]] |= can[p];
				}
			}
			M[j] -= delta;
		}
		ans[q[i].id] = can[q[i].s];
	}
	for (int i = 0; i < m; i++) puts(ans[i] ? "YES" : "NO");
}