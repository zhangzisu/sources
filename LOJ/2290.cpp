#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 15
#define MAXM 10010
#define MOD 1000000007
const int INV2 = 500000004;
const int INV4 = 250000002;
int n, m, k, pa[MAXM], pb[MAXM], pc[MAXM];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int lowbit(int x) { return x & -x; }
std::map<int, int> f[1 << MAXN];
int F(int S, int T) {
	if (!S) return 1;
	if (f[S].count(T)) return f[S][T];
	int &now = f[S][T];
	for (int i = 1; i <= m; i++) {
		if ((pa[i] & S) == pa[i] && (pb[i] & T) == pb[i] && (pa[i] & lowbit(S))) {
			up(now, 1LL * F(S ^ pa[i], T ^ pb[i]) * pc[i] % MOD);
		}
	}
	return now;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, t, a, b; i <= k; i++) {
		scanf("%d%d%d", &t, &a, &b), a--, b--;
		++m;
		pa[m] = 1 << a, pb[m] = 1 << b, pc[m] = INV2;
		if (t) {
			scanf("%d%d", &a, &b), a--, b--;
			++m;
			pa[m] = 1 << a, pb[m] = 1 << b, pc[m] = INV2;
			if ((pa[m] & pa[m - 1]) || (pb[m] & pb[m - 1])) continue;
			++m;
			pa[m] = pa[m - 1] | pa[m - 2];
			pb[m] = pb[m - 1] | pb[m - 2];
			pc[m] = (t & 1) ? INV4 : MOD - INV4;
		}
	}
	printf("%lld\n", 1LL * F((1 << n) - 1, (1 << n) - 1) * (1 << n) % MOD);
	return 0;
}
