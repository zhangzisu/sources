#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 100010
#define SQRT 316
#define MAXS 400
const int INF = (~0U) >> 1;
int n, m, a[MAXN], l[MAXN], r[MAXN], x[MAXN];
int ans[MAXN], val[SQRT << 1], tag, max;
int L[MAXS], R[MAXS], len[MAXS], sum[MAXN], pre[MAXN], all[MAXN], id[MAXN], b;
inline void modify(int oid, int bid, int op) {
	if (l[oid] > R[bid] || r[oid] < L[bid]) return;
	if (l[oid] <= L[bid] && r[oid] >= R[bid]) return tag += op, max += op, void();
	for (int i = L[bid]; i <= R[bid]; i++)
		if (l[oid] <= i && r[oid] >= i) val[i - L[bid] + 1] += op;
	max = -INF;
	for (int i = 1; i <= len[bid]; i++) max = std::max(max, val[i] + tag);
}
std::vector<int> rm[MAXN];
std::map<int, int> map;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &l[i], &r[i], &x[i]);
	while (R[b] != n) {
		++b;
		L[b] = R[b - 1] + 1;
		R[b] = std::min(b * SQRT, n);
		len[b] = R[b] - L[b] + 1;
	}
	for (int i = 1; i <= b; i++) {
		max = -INF, tag = 0;
		for (int j = 1; j <= len[i]; j++) val[j] = a[L[i] + j - 1], max = std::max(max, val[j]);
		int ca = 0, cd = 0;
		for (int j = 1, cur = 0; j <= m; j++) {
			modify(j, i, 1);
			while (cur <= m && max > 0) modify(++cur, i, -1);
			sum[j] = sum[j - 1];
			if (r[j] < L[i] || l[j] > R[i]) continue;
			if (l[j] <= L[i] && r[j] >= R[i]) {
				ans[j] = std::max(ans[j], cur);
				ca++;
				pre[++sum[all[ca] = j]] = ca;
			} else {
				id[++cd] = j;
			}
		}
		for (int j = L[i]; j <= R[i]; j++) {
			int tmp = a[j];
			for (int k = 1, cur = 0; k <= cd; k++) {
				tmp += sum[id[k]] - sum[id[k - 1]];
				if (l[id[k]] <= j && r[id[k]] >= j) {
					tmp++;
					for (; tmp > 0 && cur < cd; cur++)
						tmp -= sum[id[cur + 1]] - sum[id[cur]] + (l[id[cur + 1]] <= j && r[id[cur + 1]] >= j);
					if (tmp > 0) {
						if (tmp > sum[m] - sum[id[cur]])
							ans[id[k]] = m + 1;
						else
							ans[id[k]] = std::max(ans[id[k]], all[pre[sum[id[cur]]] + tmp]);
					} else {
						if (l[id[cur]] <= j && r[id[cur]] >= j)
							ans[id[k]] = std::max(ans[id[k]], tmp ? all[pre[sum[id[cur]]] + tmp + 1] : id[cur]);
						else
							ans[id[k]] = std::max(ans[id[k]], all[pre[sum[id[cur]] + tmp]]);
					}
				}
			}
		}
	}
	// puts("ANS:");
	// for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	// puts("REAL:");
	for (int i = 1; i <= m; i++) rm[ans[i]].push_back(x[i]);
	for (int i = 1; i <= m; i++) {
		map[x[i]]++;
		for (auto y : rm[i])
			if (!--map[y]) map.erase(y);
		printf("%lu\n", map.size());
	}
	return 0;
}