#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
inline void up(int &x, int y) {
	if (y > x) x = y;
}
int n, m, a[MAXN], b[MAXN], c[MAXN];
struct query_t {
	int l, r, k, id, ans;
	inline friend bool operator<(query_t a, query_t b) {
		return a.r < b.r;
	}
	inline void reverse() {
		int l = n - this->r + 1;
		int r = n - this->l + 1;
		this->l = l;
		this->r = r;
	}
} q[MAXN];
inline void calc() {
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	std::sort(q + 1, q + m + 1);
	for (int i = 1, cur = 1; i <= n && cur <= m; i++) {
		for (int j = 1; j * j <= a[i]; j++) {
			if (a[i] % j) continue;
			up(c[j], b[a[i] / j]);
			up(c[a[i] / j], b[j]);
		}
		b[a[i]] = i;
		for (; cur <= m && q[cur].r == i; cur++)
			q[cur].ans |= c[q[cur].k] >= q[cur].l;
	}
}
inline int cmp(query_t a, query_t b) { return a.id < b.id; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k), q[i].id = i;
	calc();
	std::reverse(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) q[i].reverse();
	calc();
	std::sort(q + 1, q + m + 1, cmp);
	for (int i = 1; i <= m; i++) puts(q[i].ans ? "Yes" : "No");
	return 0;
}