#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
lnt n, m, p, T = 1, vis[MAXN], can[MAXN];
inline lnt gcd(lnt x, lnt y) { return y ? gcd(y, x % y) : x; }
void prepare(lnt x, lnt _) {
	while (vis[x] != _) {
		vis[x] = _;
		x = x * x % p;
	}
	_ = x = x * x % p;
	lnt s = 1;
	can[x] = 1;
	x = x * x % p;
	while (x != _) {
		can[x] = 1;
		s++;
		x = x * x % p;
	}
	T = T * s / gcd(T, s);
}
lnt x[MAXN], cir[MAXN << 2][65], sum[MAXN << 2], size[MAXN << 2], cur[MAXN << 2], tag[MAXN << 2];
inline void pushDown(lnt n) {
	if (!tag[n]) return;
	(cur[n << 1] += tag[n]) %= T;
	(cur[n << 1 | 1] += tag[n]) %= T;
	(tag[n << 1] += tag[n]) %= T;
	(tag[n << 1 | 1] += tag[n]) %= T;
	sum[n << 1] = cir[n << 1][cur[n << 1]];
	sum[n << 1 | 1] = cir[n << 1 | 1][cur[n << 1 | 1]];
	tag[n] = 0;
}
inline void pushUp(lnt n, lnt l, lnt r) {
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
	size[n] = size[n << 1] + size[n << 1 | 1];
	if (size[n] == (r - l + 1)) {
		for (lnt i = 0; i < T; i++) {
			cir[n][i] = cir[n << 1][(cur[n << 1] + i) % T] + cir[n << 1 | 1][(cur[n << 1 | 1] + i) % T];
		}
	}
	cur[n] = 0;
}
void build(lnt n, lnt l, lnt r) {
	if (l == r) {
		sum[n] = x[l];
		if (can[x[l]]) {
			size[n] = 1;
			for (lnt i = 0, j = x[l]; i < T; i++, j = j * j % p) {
				cir[n][i] = j;
			}
		}
		return;
	}
	lnt mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	pushUp(n, l, r);
}
void sqr(lnt n, lnt l, lnt r, lnt L, lnt R) {
	if (l == L && r == R) {
		if (size[n] == (r - l + 1)) {
			sum[n] = cir[n][(++cur[n] >= T ? cur[n] = 0 : cur[n])];
			tag[n]++;
			return;
		}
		if (l == r) {
			sum[n] = sum[n] * sum[n] % p;
			if (can[sum[n]]) {
				size[n] = 1;
				for (lnt i = 0, j = sum[n]; i < T; i++, j = j * j % p) {
					cir[n][i] = j;
				}
			}
			return;
		}
		lnt mid = (l + r) >> 1;
		pushDown(n);
		sqr(n << 1, l, mid, L, mid);
		sqr(n << 1 | 1, mid + 1, r, mid + 1, R);
		pushUp(n, l, r);
		return;
	}
	lnt mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid)
		sqr(n << 1, l, mid, L, R);
	else if (L > mid)
		sqr(n << 1 | 1, mid + 1, r, L, R);
	else
		sqr(n << 1, l, mid, L, mid), sqr(n << 1 | 1, mid + 1, r, mid + 1, R);
	pushUp(n, l, r);
}
lnt query(lnt n, lnt l, lnt r, lnt L, lnt R) {
	if (l == L && r == R) return sum[n];
	lnt mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}

int main() {
	scanf("%lld%lld%lld", &n, &m, &p);
	for (lnt i = 1; i <= n; i++) scanf("%lld", &x[i]);
	for (lnt i = 0; i < p; i++) prepare(i, i + 1);

	build(1, 1, n);
	while (m--) {
		lnt op, l, r;
		scanf("%lld%lld%lld", &op, &l, &r);
		op ? (void)printf("%lld\n", query(1, 1, n, l, r)) : sqr(1, 1, n, l, r);
	}
	return 0;
}