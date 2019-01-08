#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
const int INF = (~0U) >> 2;
int n;
std::pair<int, int> d[MAXN], sL[MAXN], sR[MAXN], tmp[MAXN];
long long ans = 0;
inline int cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return a.second > b.second;
}
void solve(int L, int R) {
	if (L == R) return;
	int mid = (L + R) >> 1;
	solve(L, mid);
	solve(mid + 1, R);
	int topL = 0, topR = 0, cur = mid + 1;

	for (int i = L; i <= mid; i++) {
		while (cur <= R && d[cur].second > d[i].second) {
			while (topR && sR[topR].first > d[cur].first) topR--;
			sR[++topR] = d[cur++];
		}
		while (topL && sL[topL].first < d[i].first) topL--;
		sL[++topL] = d[i];

		int l = 1, r = topR, max_y = topR + 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (sR[mid].second < sL[topL - 1].second)
				max_y = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		ans += topR - max_y + 1;
	}

	topL = L, topR = mid + 1, cur = L;
	while (topL <= mid || topR <= R)
		tmp[cur++] = d[(topR <= R && (topL > mid || d[topL].second < d[topR].second) ? topR : topL)++];
	for (int i = L; i <= R; i++) d[i] = tmp[i];
}
int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &d[i].first, &d[i].second);
	std::sort(d + 1, d + n + 1);
	sL[0] = std::make_pair(INF, INF);
	solve(1, n);
	printf("%lld\n", ans);
	return 0;
}
