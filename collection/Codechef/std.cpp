#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define ll long long
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define fi first
#define se second
#define pr(x) cerr << #x << "=" << (x) << endl
#define pri(x, lo)                                                    \
	{                                                             \
		cerr << #x << "={";                                   \
		for (ll ol = 0; ol <= lo; ol++) cerr << x[ol] << ","; \
		cerr << "}" << endl;                                  \
	}
#define inf 100000000
#define N 100010
ll st[N], ed[N], pos[N], sum[N][4], now[10], num[10], a[N], size, n, m, ex[N];
ll pre[320][N][3], ans[320][320][3], i, bl, j, Q;
char ch[N];
ll solve(ll l, ll r, ll op) {
	l--;
	ll x = pos[l], y = pos[r];
	if (x != st[pos[l]]) x++;
	y--;

	//	pr(l),pr(r);pr(x),pr(y);
	if (x < y) {
		for (ll k = 0; k <= 2; k++) now[k] = ans[x][y][k];
		if (pos[l] != x) {
			for (i = ed[pos[l]]; i >= l; i--) {
				ll p = a[i];
				for (ll j = 0; j <= 2; j++) num[j] = pre[y][p][j] - pre[x - 1][p][j] + sum[p][j];
				now[0] += num[0];
				now[1] += num[1] - num[0] * i;
				now[2] += num[0] * i * i - 2ll * i * num[1] + num[2];
				sum[p][0]++;
				sum[p][1] += i;
				sum[p][2] += i * i;
			}
		}
		if (pos[r] != y) {
			for (i = st[pos[r]]; i <= r; i++) {
				ll p = a[i];
				for (ll j = 0; j <= 2; j++) num[j] = pre[y][p][j] - pre[x - 1][p][j] + sum[p][j];
				now[0] += num[0];
				now[1] += num[0] * i - num[1];
				now[2] += num[0] * i * i - 2ll * i * num[1] + num[2];
				sum[p][0]++;
				sum[p][1] += i;
				sum[p][2] += i * i;
			}
		}
		if (pos[l] != x)
			for (i = ed[pos[l]]; i >= l; i--) {
				ll p = a[i];
				sum[p][0]--;
				sum[p][1] -= i;
				sum[p][2] -= i * i;
			}
		if (pos[r] != y)
			for (i = st[pos[r]]; i <= r; i++) {
				ll p = a[i];
				sum[p][0]--;
				sum[p][1] -= i;
				sum[p][2] -= i * i;
			}
		return now[op];
	} else {
		now[0] = now[1] = now[2] = 0;
		for (i = l; i <= r; i++) {
			ll p = a[i];
			now[0] += sum[p][0];
			now[1] += sum[p][0] * i - sum[p][1];
			now[2] += sum[p][0] * i * i - 2ll * i * sum[p][1] + sum[p][2];
			sum[p][0]++;
			sum[p][1] += i;
			sum[p][2] += i * i;
		}
		for (i = l; i <= r; i++) {
			ll p = a[i];
			sum[p][0]--;
			sum[p][1] -= i;
			sum[p][2] -= i * i;
		}
		return now[op];
	}
}
int main() {
	int T = 0;
	cin >> T;
	while (T--) {
		scanf("%s", ch);
		n = strlen(ch);
		ll nw = 0;
		for (i = 1; i <= n; i++) {
			nw ^= (1 << (ch[i - 1] - 'a'));
			a[i] = ex[i] = nw;
		}
		sort(ex, ex + 1 + n);
		size = unique(ex, ex + 1 + n) - ex - 1;
		for (i = 0; i <= n; i++) a[i] = lower_bound(ex, ex + 1 + size, a[i]) - ex + 1;
		size++;
		//	pri(a,n);
		bl = sqrt(n);
		for (i = 0; i <= n; i++) {
			pos[i] = (i - 1) / bl + 1;
			if (pos[i] != pos[i - 1]) st[pos[i]] = i;
			ed[pos[i]] = i;
		}
		m = pos[n];
		//	pri(pos,n);
		//pre
		for (i = 1; i <= size; i++) sum[i][0] = sum[i][1] = sum[i][2] = 0;
		for (i = 1; i <= n; i++) {
			ll x = a[i];
			sum[x][0]++;
			sum[x][1] += i;
			sum[x][2] += i * i;
			if (i == ed[pos[i]])
				for (ll j = 1; j <= size; j++)
					for (ll k = 0; k <= 2; k++) pre[pos[i]][j][k] = sum[j][k];
		}

		//ans
		for (i = 1; i <= m; i++) {
			for (j = 1; j <= size; j++) sum[j][0] = sum[j][1] = sum[j][2] = 0;
			now[0] = now[1] = now[2] = 0;
			for (j = i; j <= m; j++) {
				for (ll k = st[j]; k <= ed[j]; k++) {
					ll x = a[k];
					now[0] += sum[x][0];
					now[1] += sum[x][0] * k - sum[x][1];
					now[2] += sum[x][0] * k * k - 2ll * k * sum[x][1] + sum[x][2];
					sum[x][0]++;
					sum[x][1] += k;
					sum[x][2] += k * k;
				}
				for (ll k = 0; k <= 2; k++) ans[i][j][k] = now[k];
			}
		}

		//	for (i=1;i<=m;i++) for (j=i;j<=m;j++) for (ll k=0;k<=2;k++) printf("ans[%d][%d][%d]=%d\n",i,j,k,ans[i][j][k]);
		//	for (i=1;i<=m;i++) for (j=1;j<=size;j++) for (ll k=0;k<=2;k++) printf("pre[%d][%d][%d]=%d\n",i,j,k,pre[i][j][k]);

		for (i = 1; i <= size; i++) sum[i][0] = sum[i][1] = sum[i][2] = 0;
		//solve
		ll A = 0, B = 0;
		scanf("%lld", &Q);
		ll x, y, d;
		while (Q--) {
			scanf("%lld %lld %lld", &x, &y, &d);
			ll L = (x + A) % n + 1, R = (y + B) % n + 1;
			if (L > R) swap(L, R);
			ll ans = solve(L, R, d);
			printf("%lld\n", ans);
			A = B;
			B = ans;
		}
		for (i = 0; i <= n; i++) pos[i] = st[i] = ed[i] = 0, a[i] = 0;
	}
	return 0;
}