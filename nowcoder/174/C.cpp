#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10000010
typedef long long lnt;
int t, n, k;
lnt l, a[MAXN], b[MAXN];
inline bool safeCompare(lnt a, lnt b) {
	return a <= b / k ? a * k < b : 0;
}
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%lld", &k, &l);
		a[0] = b[0] = 1;
		for (int cur = n = 0; a[n] < l; n++) {
			a[n + 1] = b[n] + 1;
			while (safeCompare(a[cur + 1], a[n + 1])) cur++;
			b[n + 1] = safeCompare(a[cur], a[n + 1]) ? b[cur] + a[n + 1] : a[n + 1];
		}
		puts(l == a[n] ? "DOG" : "GOD");
	}
	return 0;
}