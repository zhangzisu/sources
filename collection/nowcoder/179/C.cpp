#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
typedef int matrix[MAXN][MAXN];
typedef int vector[MAXN];
int n, m, q;
matrix f, g, data[32];
vector s, t;
inline void mul(matrix& a, matrix& b, matrix& c) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				c[i][j] |= a[i][k] && b[k][j];
			}
		}
	}
}
inline void mul(vector& a, matrix& b, vector& c) {
	for (int i = 1; i <= n; i++) c[i] = 0;
	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= n; k++) {
			c[j] |= a[k] && b[k][j];
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		g[u][v] = 1;
	}
	for (int i = 0; i < 32; i++) {
		memcpy(data[i], g, sizeof(g));
		mul(g, g, f);
		memcpy(g, f, sizeof(f));
	}
	scanf("%d", &q);
	for (int l, a, b; q; q--) {
		scanf("%d%d%d", &l, &a, &b);
		for (int i = 1; i <= n; i++) s[i] = a == i;
		for (int i = 0; i < 32; i++) {
			if ((l >> i) & 1) {
				mul(s, data[i], t);
				memcpy(s, t, sizeof(t));
			}
		}
		puts(s[b] ? "YES" : "NO");
	}
	return 0;
}