#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 100010
#define LOGN 20
#define MOD 1000000007
int n, m, p[MAXN * LOGN];
inline int gP(int x, int y) {
    return x * 20 + y;
}
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    p[x] = y;
	// printf("%d %d\n", x, y);
}
inline void assert(bool oper) {
    if (!oper) puts("0"), exit(0);
}
std::set<int> S;
inline int lc(int x, int y) { return gP(x, y - 1); }
inline int rc(int x, int y) { return gP(x + (1 << (y - 1)), y - 1); }
inline int lc(int x) { return lc(x / 20, x % 20); }
inline int rc(int x) { return rc(x / 20, x % 20); }
inline void output(int x) { printf("(%d, %d)", x / 20, x % 20); }
inline int fpow(int x, int p){
	int y = 1;
	while(p){
		if(p & 1)y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
		p >>= 1;
	}
	return y;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 20; j++)
            p[gP(i, j)] = gP(i, j);

    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        assert(b - a == d - c);
        for (int i = 19; ~i; i--) {
            if (a + (1 << i) - 1 <= b) {
                merge(gP(a, i), gP(c, i));
                a += 1 << i;
                c += 1 << i;
            }
        }
    }

    for (int i = 19; i; i--) {
        for (int j = 1; j <= n; j++) {
            if (j + (1 << i) - 1 > n) break;
            int now = gP(j, i);
            int prt = find(now);
			// printf("NP : %d %d\n", now, prt);
            merge(lc(now), lc(prt));
            merge(rc(now), rc(prt));
        }
    }

    for (int i = 1; i <= n; i++) S.insert(find(gP(i, 0)));
    printf("%lld\n", 9LL * fpow(10, S.size() - 1) % MOD);
}