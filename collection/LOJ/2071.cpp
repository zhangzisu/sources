#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 2510
const double EPS = 1e-4;
int k, n, s[MAXN], p[MAXN], size[MAXN];
double v[MAXN], f[MAXN][MAXN];
std::vector<int> next[MAXN];
void d(int x) {
	size[x] = 1;
	for (auto y : next[x]) d(y), size[x] += size[y];
}
void dp(int x) {
	for (int i = 0; i <= size[x]; i++) f[x][i] = -1e10;
	f[x][0] = 0, f[x][1] = v[x];
	for (auto y : next[x]) {
		dp(y);
		for (int i = size[x]; i; i--) {
			for (int j = size[y]; ~j; j--) {
				f[x][i + j] = std::max(f[x][i + j], f[x][i] + f[y][j]);
			}
		}
	}
}
inline bool judge(double mid) {
	for (int i = 1; i <= n; i++) v[i] = p[i] - mid * s[i];
	dp(0);
	return f[0][k + 1] >= 0;
}
int main() {
	scanf("%d%d", &k, &n);
	double l = 0, r = 0;
	for (int i = 1, x; i <= n; i++) {
		scanf("%d%d%d", &s[i], &p[i], &x);
		next[x].push_back(i);
		r = std::max(r, 1. * p[i] / s[i]);
	}
	d(0);
	while (r - l > EPS) {
		double mid = (l + r) / 2;
		(judge(mid) ? l : r) = mid;
	}
	printf("%.3f\n", (l + r) / 2);
	return 0;
}