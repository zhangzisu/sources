#include <algorithm>
typedef long long lnt;
#ifndef DEBUG
#include "gap.h"
#else
#include <cassert>
#include <cstdio>
#include <cstdlib>
int subtask_num, N;
lnt A[100001];
lnt call_count;
void MinMax(lnt s, lnt t, lnt *mn, lnt *mx) {
	int lo = 1, hi = N, left = N + 1, right = 0;
	assert(s <= t && mn != NULL && mx != NULL);
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (A[mid] >= s)
			hi = mid - 1, left = mid;
		else
			lo = mid + 1;
	}
	lo = 1, hi = N;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (A[mid] <= t)
			lo = mid + 1, right = mid;
		else
			hi = mid - 1;
	}
	if (left > right)
		*mn = *mx = -1;
	else {
		*mn = A[left];
		*mx = A[right];
	}
	if (subtask_num == 1)
		call_count++;
	else if (subtask_num == 2)
		call_count += right - left + 2;
}
#endif
const lnt INF = 1e18;

lnt cao(int n) {
	lnt min, max, ans = 0;
	MinMax(0, INF, &min, &max);
	if (n == 2) return max - min;
	for (int i = 1; i < (n + 1) / 2; i++) {
		lnt tmin, tmax;
		MinMax(min + 1, max - 1, &tmin, &tmax);
		if (!~tmin || !~tmax) break;
		ans = std::max(ans, tmin - min);
		ans = std::max(ans, max - tmax);
		min = tmin;
		max = tmax;
		if (max - min <= 1) break;
	}
	return ans = std::max(ans, max - min);
}

lnt gao(int n) {
	lnt min, max, ans = 0;
	MinMax(0, INF, &min, &max);
	if (n == 2) return max - min;
	lnt len = max - min - 1;
	lnt gap = (len + n - 3) / (n - 2);
	lnt l = min + 1, r;
	for (int i = 2; i < n; i++) {
		r = std::min(l + gap - 1, max - 1);
		lnt tmin, tmax;
		MinMax(l, r, &tmin, &tmax);
		if (~tmin && ~tmax) {
			ans = std::max(ans, tmin - min);
			min = tmax;
		}
		l = r + 1;
	}
	return ans = std::max(ans, max - min);
}

lnt findGap(int T, int N) { return T == 1 ? cao(N) : gao(N); }

#ifdef DEBUG
int main() {
	assert(2 == scanf("%d%d", &subtask_num, &N));
	assert(1 <= subtask_num && subtask_num <= 2);
	assert(2 <= N && N <= 100000);
	for (int i = 1; i <= N; i++) assert(1 == scanf("%lld", A + i));
	for (int i = 1; i < N; i++) assert(A[i] < A[i + 1]);
	printf("%lld\n", findGap(subtask_num, N));
	printf("%lld\n", call_count);
}
#endif