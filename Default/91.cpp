#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
struct sam_t {
	int son[26], len, link;
	inline sam_t(int len = 0) : len(len) { memset(son, 0, sizeof(son)), link = 0; }
	inline sam_t(const sam_t &p, int len = 0) : len(len) { memcpy(son, p.son, sizeof(son)), link = p.link; }
	inline int &operator[](int i) { return son[i]; }
} sam[MAXN];
int last = 1, cur = 1;
inline int extend(int x) {
	int p, q, r, s;
	for (sam[p = ++cur] = sam_t(sam[q = last].len + 1), last = p; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
	if (!q) return sam[p].link = 1, p;
	if (sam[r = sam[q][x]].len == sam[q].len + 1) return sam[p].link = r, p;
	for (sam[s = ++cur] = sam_t(sam[r], sam[q].len + 1); q && sam[q][x] == r; q = sam[q].link) sam[q][x] = s;
	return sam[p].link = sam[r].link = s, p;
}
int n, k, a[MAXN], b[MAXN], sum[MAXN], id[MAXN], pos[MAXN], max[MAXN];
char buf[MAXN];
long long ans = 0;
int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	for (int i = 1; i <= n; i++) pos[i] = extend(a[i] = buf[i] - 'a');
	scanf("%s", buf + 1);
	for (int i = 1; i <= n; i++) b[i] = b[i - 1] + (buf[i] == '0');
	scanf("%d", &k);
	for (int p = 0, i = 1; i <= n; i++) {
		while (b[i] - b[p] > k) p++;
		max[pos[i]] = std::max(max[pos[i]], i - p);
	}
	for (int i = 1; i <= cur; i++) sum[sam[i].len]++;
	for (int i = 1; i <= n; i++) sum[i] += sum[i - 1];
	for (int i = 1; i <= cur; i++) id[sum[sam[i].len]--] = i;
	for (int _ = cur; _ >= 1; _--) {
		int x = id[_];
		max[sam[x].link] = std::max(max[sam[x].link], max[x]);
	}
	for (int i = 2; i <= cur; i++) ans += std::max(0, std::min(max[i], sam[i].len) - sam[sam[i].link].len);
	printf("%lld\n", ans);
	return 0;
}
