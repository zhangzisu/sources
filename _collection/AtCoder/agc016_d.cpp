#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 200010
std::map<int, int> M;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN], p[MAXN], n, m;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[0] ^= a[i];
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]), b[0] ^= b[i];
	memcpy(c, a, sizeof(c));
	memcpy(d, b, sizeof(d));
	std::sort(c, c + n + 1);
	std::sort(d, d + n + 1);
	for (int i = 0; i <= n; i++)
		if (c[i] != d[i]) return puts("-1"), 0;
	for (int i = 0; i <= n; i++)
		if (a[i] != b[i]) goto fail;
	return puts("0"), 0;
fail:
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		if (!i || a[i] != b[i]) {
			if (!M.count(a[i])) {
				M[a[i]] = ++m;
				p[m] = m;
			}
			if (!M.count(b[i])) {
				M[b[i]] = ++m;
				p[m] = m;
			}
			int A = find(M[a[i]]), B = find(M[b[i]]);
			if (A != B) p[A] = B;
			ans += i > 0;
		}
	}
	for (int i = 1; i <= m; i++)
		if (find(i) == i) ans++;
	printf("%d\n", ans - 1);
	return 0;
}