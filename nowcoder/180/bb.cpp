#include <bits/stdc++.h>
#define N 5000005
#define next(n, i) (n / (n / i + 1))

typedef long long ll;

const int mod = 2333;

int D;
int pn, c[N], p[900005], d[N], fy[N];

void sieve(int n) {
	int i, j, v;
	d[1] = 1;
	for (i = 2; i <= n; ++i) {
		if (!c[i]) p[pn++] = i, d[i] = 2, fy[i] = 1;
		for (j = 0; j < pn; ++j) {
			if ((v = i * p[j]) > n) break;
			c[v] = p[j];
			if (i % p[j]) d[v] = d[i] * 2, fy[v] = d[i];
			else {d[v] = d[i] + fy[i], fy[v] = fy[i]; break;}
		}
		d[i] = (d[i - 1] + d[i]) % mod;
	}
}

int calc(ll n){
	if (n < N) return d[n];
	int sq = sqrt(n), i, fy = 0;
	for (i = 1; i <= sq; ++i) fy = (fy + n / i) % mod;
	return (fy * 2ll - (ll)sq * sq) % mod;
}

int solve(ll x) {
	int j; ll ret = calc(x);
	for (j = 1; j <= D; ++j) ret -= x / j;
	return ret % mod;
}

int main(){
	ll n; int i, j, ans = 0;
	sieve(N - 1);
	scanf("%lld", &n);
	D = cbrt(n);
	for (i = D; i; i = j) {
		j = next(n, i);
		ans += solve(n / i) * (i - j);
	}
	ans += ans >> 31 & mod;
	ans = (ans * 3 + (ll)D * D * D) % mod;
	printf("%d\n", ans);
	return 0;
}