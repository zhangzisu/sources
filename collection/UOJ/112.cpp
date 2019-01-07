#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 200010
typedef long long lnt;
int k, n, a[MAXN], b[MAXN];
char buf0[5], buf1[5];
lnt ans = 0, pre[MAXN], nxt[MAXN];
struct MSS {
	std::set<std::pair<int, int>> S;
	int left, right, count;
	std::set<std::pair<int, int>>::iterator it;
	MSS() {
		S.clear();
		left = right = count = 0;
	}
	inline void add(int x) {
		if (S.empty()) {
			S.emplace(x, ++count);
			it = S.begin();
		} else {
			(x < it->first ? left : right)++;
			S.emplace(x, ++count);
			if (left < right - 1) left++, right--, it++;
			if (left > right) left--, right++, it--;
		}
	}
	inline int get() {
		return it->first;
	}
	inline void clear() {
		S.clear();
		left = right = count = 0;
	}
} mss;
struct range_t {
	int l, r;
} ranges[MAXN];
int v[MAXN], cntL[MAXN], cntR[MAXN], t;
lnt sumL[MAXN], sumR[MAXN];
inline int lowbit(int x) { return x & -x; }
int main() {
	scanf("%d%d", &k, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s%d%s%d", buf0, &a[i], buf1, &b[i]);
		if (a[i] > b[i]) std::swap(a[i], b[i]);
		if (buf0[0] == buf1[0]) {
			ans += b[i] - a[i];
			n--, i--;
		} else {
			ans += b[i] - a[i] + 1;
			v[++t] = ranges[i].l = a[i];
			v[++t] = ranges[i].r = b[i];
		}
	}
	if (!n) return printf("%lld\n", ans), 0;
	if (n == 1) return printf("%lld\n", ans), 0;
	std::sort(v + 1, v + t + 1);
	t = std::unique(v + 1, v + t + 1) - v - 1;
	if (k == 1) {
		for (int i = 1; i <= n; i++) {
			mss.add(a[i]);
			mss.add(b[i]);
		}
		int mid = mss.get();
		for (int i = 1; i <= n; i++) {
			if (mid < a[i]) {
				ans += (a[i] - mid) * 2;
			} else if (mid > b[i]) {
				ans += (mid - b[i]) * 2;
			}
		}
		printf("%lld\n", ans);
	} else {
		std::sort(ranges + 1, ranges + n + 1, [](range_t a, range_t b) { return a.l + a.r < b.l + b.r; });
		for (int i = 1; i <= n; i++) {
			mss.add(ranges[i].l);
			mss.add(ranges[i].r);
			int l = std::lower_bound(v + 1, v + t + 1, ranges[i].l) - v;
			int r = std::lower_bound(v + 1, v + t + 1, ranges[i].r) - v;
			int mid = mss.get(), count;
			int m = std::lower_bound(v + 1, v + t + 1, mid) - v;
			lnt tmp;
			tmp = count = 0;
			for (int x = r; x <= t; x += lowbit(x)) cntL[x]++, sumL[x] += ranges[i].r;
			for (int x = m - 1; x; x -= lowbit(x)) count += cntL[x], tmp += sumL[x];
			pre[i] += (1LL * count * mid - tmp) * 2;
			tmp = count = 0;
			for (int x = l; x; x -= lowbit(x)) cntR[x]++, sumR[x] += ranges[i].l;
			for (int x = m + 1; x <= t; x += lowbit(x)) count += cntR[x], tmp += sumR[x];
			pre[i] += (tmp - 1LL * count * mid) * 2;
		}
		mss.clear();
		memset(cntL, 0, sizeof(cntL));
		memset(cntR, 0, sizeof(cntR));
		memset(sumL, 0, sizeof(sumL));
		memset(sumR, 0, sizeof(sumR));
		for (int i = n; i >= 1; i--) {
			mss.add(ranges[i].l);
			mss.add(ranges[i].r);
			int l = std::lower_bound(v + 1, v + t + 1, ranges[i].l) - v;
			int r = std::lower_bound(v + 1, v + t + 1, ranges[i].r) - v;
			int mid = mss.get(), count = 0;
			int m = std::lower_bound(v + 1, v + t + 1, mid) - v;
			lnt tmp;
			tmp = count = 0;
			for (int x = r; x <= t; x += lowbit(x)) cntL[x]++, sumL[x] += ranges[i].r;
			for (int x = m - 1; x; x -= lowbit(x)) count += cntL[x], tmp += sumL[x];
			nxt[i] += (1LL * count * mid - tmp) * 2;
			tmp = count = 0;
			for (int x = l; x; x -= lowbit(x)) cntR[x]++, sumR[x] += ranges[i].l;
			for (int x = m + 1; x <= t; x += lowbit(x)) count += cntR[x], tmp += sumR[x];
			nxt[i] += (tmp - 1LL * count * mid) * 2;
		}
		lnt res = (~0ULL) >> 1;
		for (int i = 1; i < n; i++) res = std::min(res, pre[i] + nxt[i + 1]);
		printf("%lld\n", res + ans);
	}
	return 0;
}