#include <cstdio>
#include <cstring>

int C[2020];
int K[2020];
int m;
int b[2020];
int a[2020];
int p = 1000000007;
int n;
void mul(int a[], const int b[]) {
	int w[2020] = {};
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			w[i + j] = (w[i + j] + (long long)a[i] * b[j]) % p;
		}
	}

	for (int i = 2 * m - 2; i >= m; i--) {
		for (int k = 1; k <= m; k++) {
			w[i - k] = (w[i - k] + (long long)w[i] * K[k]) % p;
		}
	}

	for (int i = 0; i < m; i++) {
		a[i] = w[i];
	}
}
int main() {
	a[0] = 1;
	b[1] = 1;
	scanf("%d%d", &n, &m);
	K[1] = 1;
	C[0] = 1;
	for (int i = 1; i < m - 1; i++) {
		K[i + 1] = (long long)K[i] * i % p;
	}
	for (int i = 1; i < m; i++) {
		K[i] = (long long)K[i] * (m - i) % p;
		C[i] = (long long)C[i - 1] * m % p;
	}
	for (; n; mul(b, b)) {
		if (n & 1) {
			mul(a, b);
		}
		if (!(n >>= 1)) {
			break;
		}
	}
	for(int i = 0;i < m;i++)printf("DBG :: %d\n", a[i]);
	int ans = 0;
	for (int i = 0; i < m; i++) {
		ans = (ans + (long long)a[i] * C[i]) % p;
	}
	printf("%d\n", ans);
	return 0;
}