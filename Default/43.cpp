#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
// Max c_i * x_i
// St A * X = B
const double EPS = 1e-8, INF = 1e18;
double a[MAXN][MAXN], b[MAXN], c[MAXN], ans;
int n, m, k;
// 这道题不用关心具体的基变量是什么
// 我们可以默认x_i = b[i] - \sum a[i][j] * x_j
inline void pivot(int i, int j) {
	b[i] /= a[i][j];
	for (int k = 1; k <= n; k++) {
		if (k != j) a[i][k] /= a[i][j];
	}
	a[i][j] = 1 / a[i][j];
	for (int k = 1; k <= m; k++) {
		// 对约束条件k，代换其中的x_j
		if (k != i && std::abs(a[k][j]) > EPS) {
			b[k] -= b[i] * a[k][j];
			for (int l = 1; l <= n; l++) {
				if (l != j) a[k][l] -= a[i][l] * a[k][j];
			}
			a[k][j] = -a[k][j] * a[i][j];
		}
	}
	ans += b[i] * c[j];
	// 变换系数c
	for (int k = 1; k <= n; k++) {
		if (k != j) c[k] -= a[i][k] * c[j];
	}
	c[j] = -c[j] * a[i][j];
}
inline void simplex() {
	for (int i, j;;) {
		for (j = 1; j <= n; j++) {
			// 找到一个变量j，使得其在答案函数中的系数>0
			// 下一步将将其入基
			if (c[j] > EPS) break;
		}
		if (j == n + 1) break;
		double min = INF;
		for (int k = 1; k <= m; k++) {
			// 寻找最紧的约束条件i
			if (a[k][j] > EPS && b[k] / a[k][j] < min) {
				min = b[k] / a[k][j];
				i = k;
			}
		}
		// 转置，关键点为(i,j)
		pivot(i, j);
	}
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= 3 * n; i++) scanf("%lf", &c[i]);
	for (int i = 1; i <= 2 * n + 1; i++) {
		b[++m] = k;
		for (int j = 1; j <= n; j++) {
			a[m][i + j - 1] = 1;
		}
	}
	for (int i = 1; i <= 3 * n; i++) {
		b[++m] = 1;
		a[m][i] = 1;
	}
	n *= 3;
	simplex();
	printf("%.0f\n", ans);
	return 0;
}