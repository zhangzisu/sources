#include <bits/stdc++.h>
using namespace std;
long long f[1000020];
long long s[1000020];
int t[1000020];
int n, m, p = 1000000007;
int a[1000020], mx;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		mx = max(mx, a[i]);
	}
	for (int i = 1; i <= m; i++) {
		t[i] = 1;
	}
	for (int i = 1; i <= mx; i++) {
		for (int j = i + i; j <= mx; j += i) {
			t[j] -= t[i];
			if (t[j] < 0) {
				t[j] += p;
			}
		}
	}
    for(int i = 1;i <= mx;i++)printf("mu[i] = %d\n", t[i]);
	for (int i = 1; i <= a[0]; i++) {
		f[i] = 1;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= a[i - 1]; j++) {
			s[j] = 0;
		}
		for (int j = 1; j <= a[i - 1]; j++) {
			for (int k = j; k <= a[i - 1]; k += j) {
				s[j] += f[k];
				if (s[j] >= p) {
					s[j] -= p;
				}
			}
		}
		for (int j = 1; j <= a[i]; j++) {
			f[j] = 0;
		}
		for (int j = 1; j <= a[i - 1]; j++) {
			for (int k = j; k <= a[i]; k += j) {
				printf("%d\n",(f[k] = (f[k] + s[j] * t[j]) % p));
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= a[n - 1]; i++) {
		ans += f[i];
		if (ans >= p) {
			ans -= p;
		}
	}
	printf("%d\n", ans);
	return 0;
}