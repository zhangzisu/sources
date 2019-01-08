#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define SQRT 1000
#define MAXM 32768
typedef long long lnt;
const double PI = acos(-1);
int n, k, a[MAXN], cl[MAXM], cr[MAXM], cx[MAXM];
lnt ans = 0;
struct complex {
	double x, y;
	inline complex(double x = 0, double y = 0) : x(x), y(y) {}
	inline complex friend operator*(const complex &a, const complex &b) {
		return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
	inline complex friend operator+(const complex &a, const complex &b) {
		return complex(a.x + b.x, a.y + b.y);
	}
	inline complex friend operator-(const complex &a, const complex &b) {
		return complex(a.x - b.x, a.y - b.y);
	}
};
int pro[MAXM << 1];
inline void pre(int n){
    for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		pro[i] = j;
	}
}
inline void FFT(complex *a, int n, int e) {
	for (int i = 1; i < n - 1; i++) {
		if (i < pro[i]) std::swap(a[i], a[pro[i]]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		complex wn = complex(cos(PI / i), e * sin(PI / i));
		for (int j = 0; j < n; j += t) {
			complex w(1, 0);
			for (int k = 0; k < i; k++, w = w * wn) {
				complex x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}
complex f[MAXM << 1], g[MAXM << 1];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		k = std::max(k, a[i]);
		cr[a[i]]++;
	}
	int len = 1;
	while (len <= k) len <<= 1;
	len <<= 1;
    pre(len);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = std::min(n, l + SQRT - 1);
		int m = r - l + 1;
		int *b = a + l - 1;
		for (int i = 1; i <= m; i++) cr[b[i]]--;
		for (int i = m; i >= 1; i--) {
			for (int j = 1; j < i; j++) {
				int nxt = 2 * b[i] - b[j];
				if (nxt < 0 || nxt > k) continue;
				ans += cx[nxt];
			}
			cx[b[i]]++;
		}
		for (int i = 1; i <= m; i++) {  // mid
			cx[b[i]]--;
			for (int j = 1; j < i; j++) {  // left
				int nxt = 2 * b[i] - b[j];
				if (nxt < 0 || nxt > k) continue;
				ans += cr[nxt];
			}
			for (int j = m; j > i; j--) {  // right
				int nxt = 2 * b[i] - b[j];
				if (nxt < 0 || nxt > k) continue;
				ans += cl[nxt];
			}
		}
		for (int i = 0; i < len; i++) f[i] = g[i] = 0;
		for (int i = 1; i <= k; i++) {
			f[i] = cl[i];
			g[i] = cr[i];
		}
		FFT(f, len, 1);
		FFT(g, len, 1);
		for (int i = 0; i < len; i++) f[i] = f[i] * g[i];
		FFT(f, len, -1);
		for (int i = 1; i <= m; i++) {
			ans += (lnt)round(f[2 * b[i]].x / len);
		}
		for (int i = 1; i <= m; i++) cl[b[i]]++;
	}
	printf("%lld\n", ans);
	return 0;
}