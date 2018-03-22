#include <bits/stdc++.h>
using namespace std;
int n, a[120][120], mod;
int b[120];
int c[2020];
int l;
long long m;
void C(long long m) {
	if (m == 0) {
		memset(c, 0, sizeof c);
		c[0] = 1;
	} else {
		if (m % 2 == 1) {
			C(m - 1);
			for (int i = 2 * l; i > 0; i--) {
				c[i] = (c[i] + c[i - 1]) % mod;
			}
		} else {
			C(m / 2);
			for (int i = 2 * l; i > 0; i--) {
				for (int j = 0; j < i; j++) {
					c[i] = (c[i] + (long long)c[i - j] * c[j]) % mod;
				}
			}
		}
	}
}

int main() {
	cin >> n >> m >> mod;
	fprintf(stderr, "%d %lld %d\n", n, m, mod);
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
		l = max(l, b[i]);
	}
	C(m);
	for(int i = 0;i < 10;i++)printf("%lld ", c[i]);

	// (-b[i], b[i]) -> (b[i], m - b[i])
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = c[b[i] + b[n - 1 - j]];
//			printf("%d %d %d\n", i, j, a[i][j]);
		}
	}
	long long ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			while (a[j][i] != 0) {
				int u = a[i][i] / a[j][i];
				for (int k = 0; k < n; k++) {
					int t = (a[i][k] - (long long)a[j][k] * u % mod + mod) % mod;
					a[i][k] = a[j][k];
					a[j][k] = t;
				}
				ans = -ans;
			}
		}
		ans = ans * a[i][i] % mod;
	}
	if (ans < 0) {
		ans += mod;
	}
	printf("%lld\n", ans);
	return 0;
}