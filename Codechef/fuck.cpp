#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

#ifdef ONLINE_JUDGE
char *TT, *mo, but[(1 << 15) + 2];
#define getchar() ((TT == mo && (mo = (TT = but) + fread(but, 1, 1 << 15, stdin)), TT == mo) ? 0 : *TT++)
#endif
inline int read() {
	int x = 0, c = 0, f = 1;
	for (; c < '0' || c > '9'; c = getchar()) f = c != '-';
	for (; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
	return f ? x : -x;
}
void print(ll x) {
	if (x < 0) putchar('-'), x = -x;
	if (x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 500100;
const ll inf = 0X3f3f3f3f3f3f3f3fll;

int n;
struct seg_tree {
	ll a, b, c, d;
    inline seg_tree(){
        c=d=-inf;
    }
} tr[N << 2];

inline void pushdown(int k) {
	tr[k << 1].c = max(tr[k << 1].c, tr[k].c + tr[k << 1].a);
	tr[k << 1].d = max(tr[k].d, max(tr[k << 1].d, tr[k << 1].b + tr[k].c));
	tr[k << 1].a = max(-inf, tr[k].a + tr[k << 1].a);
	tr[k << 1].b = max(tr[k << 1].b + tr[k].a, tr[k].b);

	tr[k << 1 | 1].c = max(tr[k << 1 | 1].c, tr[k].c + tr[k << 1 | 1].a);
	tr[k << 1 | 1].d = max(tr[k].d, max(tr[k << 1 | 1].d, tr[k << 1 | 1].b + tr[k].c));
	tr[k << 1 | 1].a = max(-inf, tr[k].a + tr[k << 1 | 1].a);
	tr[k << 1 | 1].b = max(tr[k << 1 | 1].b + tr[k].a, tr[k].b);
	tr[k].a = tr[k].c = 0;
    tr[k].b = tr[k].d = -inf;
}

void modify(int k, int l, int r, int x, int y, ll a, ll b) {
	if (l >= x && r <= y) {
		tr[k].a = max(-inf, tr[k].a + a);
		tr[k].b = max(tr[k].b + a, b);
		tr[k].c = max(tr[k].a, tr[k].c);
		tr[k].d = max(tr[k].b, tr[k].d);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(k);
	if (x <= mid) modify(k << 1, l, mid, x, y, a, b);
	if (y > mid) modify(k << 1 | 1, mid + 1, r, x, y, a, b);
}

inline ll query(int x) {
	register int l = 1, r = n, mid, k = 1;
	while (l < r) {
		mid = (l + r) >> 1;
		pushdown(k);
		x <= mid ? (k <<= 1, r = mid) : (k = k << 1 | 1, l = mid + 1);
	}
	return max(tr[k].a, tr[k].b);
}

inline ll query_mx(int x) {
	register int l = 1, r = n, mid, k = 1;
	while (l < r) {
		mid = (l + r) >> 1;
		pushdown(k);
		x <= mid ? (k <<= 1, r = mid) : (k = k << 1 | 1, l = mid + 1);
	}
	return max(tr[k].c, tr[k].d);
}

void build(int k, int l, int r) {
    tr[k].b = tr[k].d = -inf;
	if (l == r) {
		tr[k].a = tr[k].c = read();
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}

int main() {
	n = read();
	int Q = read();
	build(1, 1, n);
	register int opt, x, y, val;
	while (Q--) {
		opt = read();
		x = read();
		switch (opt) {
			case 1:
				y = read(), val = read();
				modify(1, 1, n, x, y, val, -inf);
				break;
			case 2:
				y = read(), val = read();
				modify(1, 1, n, x, y, -val, -inf);
				break;
			case 3:
				y = read(), val = read();
				modify(1, 1, n, x, y, -inf, val);
				break;
			case 4:
				print(query(x));
				puts("");
				break;
			case 5:
				print(query_mx(x));
				puts("");
				break;
		}
	}
	return 0;
}