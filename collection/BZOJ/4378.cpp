#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
typedef long long lnt;
int n, m, k, t[MAXN], x[MAXN], y[MAXN], v[MAXN], w[MAXN];
lnt sum[MAXN], bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void sadd(int x, int v) {
	for (; x <= k; x += lowbit(x)) sum[x] += v;
}
inline lnt sqry(int x) {
	lnt v = 0;
	for (; x; x -= lowbit(x)) v += sum[x];
	return v;
}
inline void cadd(int x, int v) {
	for (; x; x -= lowbit(x)) bit[x] += v;
}
inline lnt cqry(int x) {
	lnt v = 0;
	for (; x <= k; x += lowbit(x)) v += bit[x];
	return v;
}
char buf[5];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%s%d%d", buf, x + i, y + i);
		if ((t[i] = buf[0] == 'U')) v[++k] = y[i];
	}
	std::sort(v + 1, v + k + 1);
	for (int i = 1; i <= m; i++) {
        int ty = std::lower_bound(v + 1, v + k + 1, y[i]) - v;
		if (t[i]) {
			int &W = w[x[i]];
			if (W) sadd(W, -v[W]), cadd(W, -1);
			if (W = ty) sadd(W, v[W]), cadd(W, 1);
		} else {
			lnt count = cqry(ty);
			if (count >= x[i]) {
				puts("TAK");
			} else {
				lnt sum = sqry(ty - 1);
				puts(sum >= (x[i] - count) * y[i] ? "TAK" : "NIE");
			}
		}
	}
	return 0;
}