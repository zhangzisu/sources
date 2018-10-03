#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 2010;

const int mod = 998244353;

int f[maxn][maxn], g[maxn][maxn];
int s[maxn][maxn], jc[maxn];
//fij i个数，最大为j，两两之差不超过k
//gij i个数，分成j份，多重集排列系数和

//x-y <= k
//y >= x-k
int n, m, k;

int main() {
	cin >> n >> m >> k;
	jc[0] = 1;
	for (int i = 1; i <= n; i++) jc[i] = 1LL * jc[i - 1] * i % mod;
	g[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			g[i][j] = (g[i - 1][j - 1] + 1LL * j * g[i - 1][j] % mod) % mod;
		}
	}
	f[1][0] = s[1][0] = 1;
	for (int j = 0; j <= m; j++) {
		s[1][j] = (s[1][j - 1] + f[1][j]) % mod;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			f[i][j] = (s[i - 1][j - 1] - ((j - k - 1 >= 0) ? s[i - 1][j - k - 1] : 0) % mod + mod) % mod;
		}
		for (int j = 0; j <= m; j++) {
			if (j)
				s[i][j] = (s[i][j - 1] + f[i][j]) % mod;
			else
				s[i][j] = f[i][j];
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		(ans += 1LL * g[n][i] * s[i][m] % mod * jc[i] % mod) %= mod;
	}
	cout << ans << endl;
	return 0;
}