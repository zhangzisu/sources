#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
#define MAXN 100010
typedef long long lnt;
int max[MAXN << 2], tag[MAXN << 2];
inline void pushDown(int n) {
	if (tag[n]) {
		max[n << 1] += tag[n];
		tag[n << 1] += tag[n];
		max[n << 1 | 1] += tag[n];
		tag[n << 1 | 1] += tag[n];
		tag[n] = 0;
	}
}
inline void add(int n, int l, int r, int L, int R, int v) {
	if (L > R) return;
	if (l == L && r == R) return max[n] += v, tag[n] += v, void();
	pushDown(n);
	int mid = (l + r) >> 1;
	if (R <= mid) {
		add(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		add(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		add(n << 1, l, mid, L, mid, v);
		add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
inline void set(int n, int l, int r, int p, int v) {
	if (l == r) return max[n] = v, void();
	pushDown(n);
	int mid = (l + r) >> 1;
	p <= mid ? set(n << 1, l, mid, p, v) : set(n << 1 | 1, mid + 1, r, p, v);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}

ll merge_count(vector<int> &a) {
	int n = a.size();
	if (n <= 1) return 0;
	vector<int> b(a.begin(), a.begin() + n / 2);
	vector<int> c(a.begin() + n / 2, a.end());
	ll res = 0;
	res += merge_count(b);
	res += merge_count(c);
	for (int ai = 0, bi = 0, ci = 0; ai < n; ++ai) {
		if (ci == (int)c.size() || (bi < (int)b.size() && b[bi] <= c[ci])) {
			a[ai] = b[bi++];
		} else {
			a[ai] = c[ci++];
			res += n / 2 - bi;
		}
	}
	return res;
}

int N, A[1000010];
int Yu[1000010];

vector<int> Ux, Uy, L;
bool usd[1000010];

pair<int, int> get_u_range(int i) {
	return mp(upper_bound(all(Uy), A[i]) - Uy.begin(),
		  upper_bound(all(Ux), i) - Ux.begin());
}

ll solve() {
	vector<int> a(A, A + N);
	ll org = merge_count(a), ans = org + 1;
	rep(i, N - 1) {
		if (a[i] == a[i + 1]) {
			--ans;
			break;
		}
	}

	for (int i = 0; i < N; ++i) {
		if (Ux.empty() || A[Ux.back()] < A[i]) {
			usd[i] = true;
			Ux.pb(i);
			Uy.pb(A[i]);
		}
	}
	for (int i = N - 1; i >= 0; --i) {
		if ((L.empty() || A[L.back()] > A[i]) && !usd[i]) {
			L.pb(i);
			usd[i] = true;
		}
	}
	reverse(all(L));

	vector<int> Mx, My;
	rep(i, N) if (!usd[i]) Mx.pb(i);
	{
		vector<pair<int, int> > tmp;
		rep(i, Mx.size()) tmp.pb(mp(A[Mx[i]], Mx[i]));
		sort(all(tmp));
		rep(i, tmp.size()) My.pb(tmp[i].second);
	}
	int Un = Ux.size(), Ln = L.size(), Mn = Mx.size();

	memset(segt_max, 0, sizeof(segt_max));
	memset(segt_dif, 0, sizeof(segt_dif));

	int mxi = 0, myi = 0;
	rep(li, Ln) {
		int l = L[li];

		for (; mxi < Mn && Mx[mxi] < l; ++mxi) {  // In
			pair<int, int> ur = get_u_range(Mx[mxi]);
			segt_add(ur.first, ur.second, +1, 0, 0, Un);
			if (ur.first - 1 >= 0 && A[Ux[ur.first - 1]] == A[Mx[mxi]]) --ur.first;
			segt_add(ur.first, ur.second, +1, 0, 0, Un);
		}
		for (; myi < Mn && A[My[myi]] < A[l]; ++myi) {  // Out
			pair<int, int> ur = get_u_range(My[myi]);
			segt_add(ur.first, ur.second, -1, 0, 0, Un);
			if (ur.first - 1 >= 0 && A[Ux[ur.first - 1]] == A[My[myi]]) --ur.first;
			segt_add(ur.first, ur.second, -1, 0, 0, Un);
		}
		for (int k = 0; myi + k < Mn && A[My[myi + k]] == A[l]; ++k) {  // Border
			pair<int, int> ur = get_u_range(My[myi + k]);
			if (ur.first - 1 >= 0 && A[Ux[ur.first - 1]] == A[My[myi]]) --ur.first;
			segt_add(ur.first, ur.second, -1, 0, 0, Un);
		}

		pair<int, int> ur = get_u_range(l);
		if (ur.first < ur.second) {
			int tmp = segt_max[0];
			ans = min(ans, org - tmp - 1);
		}
		for (; myi < Mn && A[My[myi]] == A[l]; ++myi) {  // Out
			pair<int, int> ur = get_u_range(My[myi]);
			segt_add(ur.first, ur.second, -1, 0, 0, Un);
		}
	}

	return ans;
}

int main() {
	scanf("%d", &N);
	rep(i, N) scanf("%d", &A[i]);

	vector<int> nums(A, A + N);
	sort(all(nums));
	nums.erase(unique(all(nums)), nums.end());
	rep(i, N) A[i] = lower_bound(all(nums), A[i]) - nums.begin();

	printf("%lld\n", solve());
	return 0;
}