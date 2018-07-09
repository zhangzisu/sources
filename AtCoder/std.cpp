#include <bits/stdc++.h>

#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(v) int(v.size())
#define pii pair<int, int>
#define mp make_pair
#define f first
#define s second

using namespace std;

const int N = (int) 3e4 + 10;
const int K = (int) 4e2 + 10;
const int mod = (int) 1e9 + 7;

int n, k, m;
int a[N];

int mult(int x, int y) {
	return 1ll * x * y % mod;
}

void add(int &x, int y) {
	x += y;
	if (x >= mod) 
		x -= mod;
	if (x < 0) 
		x += mod;
}

int sum(int x, int y) {
	add(x, y);
	return x;
}

int bp(int x, int y) {
	int ans = 1;
	while (y) {
		if (y & 1)
			ans = mult(ans, x);
		x = mult(x, x);
		y >>= 1;
	}
	return ans;
}

int cnt[N][K]; // cnt(i, j) = # of seq of len i such that last j are unique (but j + 1 not) 
int dp[N][K]; // dp(i, j) = summa po vsem posledovatelnostyam a, kol-vo posledovatelnyh m razlichnyh v a
int f[N], inv[N];

int dp1[N][K], dp2[N][K], pref[N];

int solve() {
	map<int, int> id;
	for (int i = 1, ptr = 1; i <= m; i++) {
		if (ptr <= id[a[i]])
			ptr = id[a[i]] + 1;
		if (i - ptr + 1 == k) 
			return 0;
		id[a[i]] = i;
	}
	int ans;
	cnt[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		pref[0] = 0;
		for (int j = 1; j < k; j++) {
			add(pref[j] = pref[j - 1], cnt[i - 1][j]);
		}
		for (int j = 1; j < k; j++) {
			add(cnt[i][j], mult(cnt[i - 1][j - 1], k - j + 1));
			add(cnt[i][j], sum(pref[k - 1], -pref[j - 1]));
		}
		pref[0] = 0;
		for (int j = 1; j < k; j++) {
			add(pref[j] = pref[j - 1], dp[i - 1][j]);
		}
		for (int j = 1; j < k; j++) {
			add(dp[i][j], mult(dp[i - 1][j - 1], k - j + 1));
			add(dp[i][j], sum(pref[k - 1], -pref[j - 1]));
			if (j >= m)
				add(dp[i][j], cnt[i][j]);
		}
	}
	for (int i = 1; i + k - 1 <= m; i++) {
		set<int> st;
		for (int j = 1; j <= k; j++) {
			st.insert(a[i + j - 1]);
		}
		if (sz(st) == k) {
			return 0;
		}
	}
	if (sz(id) == m) { 
		int sum = 0;
		for (int i = 1; i < k; i++) 
			add(sum, dp[n][i]);
		//cout << "#= " << sum << "\n";
		return mult(mult(sum, f[k - m]), inv[k]);
	}
	set<int> st;
	int ptr1 = -1, ptr2 = -1;
	for (int i = 1; i <= m; i++) {
		st.insert(a[i]);
		if (sz(st) != i) {
			ptr1 = i - 1;
			break;
		}
	}
	st.clear();
	for (int i = m; i >= 1; i--) {
		st.insert(a[i]);
		if (sz(st) != m - i + 1) {
			ptr2 = m - i;
			break;
		}
	}
	cout << ptr1 << ' ' << ptr2 << endl;
	dp1[0][ptr1] = 1;
	for (int i = 1; i <= n; i++) {
		pref[0] = 0;
		for (int j = 1; j < k; j++) {
			add(pref[j] = pref[j - 1], dp1[i - 1][j]);
		}
		for (int j = 1; j < k; j++) {
			add(dp1[i][j], mult(dp1[i - 1][j - 1], k - j + 1));
			add(dp1[i][j], sum(pref[k - 1], -pref[j - 1]));
		}
	}
	dp2[0][ptr2] = 1;
	for (int i = 1; i <= n; i++) {
		pref[0] = 0;
		for (int j = 1; j < k; j++) {
			add(pref[j] = pref[j - 1], dp2[i - 1][j]);
		}
		for (int j = 1; j < k; j++) {
			add(dp2[i][j], mult(dp2[i - 1][j - 1], k - j + 1));
			add(dp2[i][j], sum(pref[k - 1], -pref[j - 1]));
		}
	}
	ans = 0;
	for (int i = 0; i <= n - m; i++) {
		int cnt_left = 0, cnt_right = 0;
		for (int j = 1; j < k; j++) {
			add(cnt_left, dp1[i][j]);
			add(cnt_right, dp2[n - m - i][j]);
		}
		add(ans, mult(cnt_left, cnt_right));
	}
	return ans;
}

int main() {
	//	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	cin >> n >> k >> m;
	for (int i = 0; i <= k; i++) {
		f[i] = i ? mult(f[i - 1], i) : 1;
		inv[i] = bp(f[i], mod - 2);
	}
	for (int i = 1; i <= m; i++) {
		cin >> a[i];
	}
	cout << sum(mult(n - m + 1, bp(k, n - m)), -solve());
	return 0;
}
