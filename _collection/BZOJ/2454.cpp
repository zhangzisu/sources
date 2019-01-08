#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MOD 1000000007
typedef long long lnt;
struct data {
	lnt a, b, c;
	inline int friend operator==(const data& a, const data& b) {
		return a.a == b.a && a.b == b.b && a.c == b.c;
	}
	inline int friend operator!=(const data& a, const data& b) {
		return !(a == b);
	}
	inline int friend operator<(const data& a, const data& b) {
		if (a.a != b.a) return a.a < b.a;
		if (a.b != b.b) return a.b < b.b;
		return a.c < b.c;
	}
	inline int isRoot() const {
		return b - a == c - b;
	}
	inline int up() {
		lnt dl = b - a;
		lnt dr = c - b;
		if (dl < dr) {
			a += dl, b += dl;
			return 0;
		} else {
			b -= dr, c -= dr;
			return 1;
		}
	}
} A, B, C, D;
std::map<data, int> M;
int m, n, f[300][300][300], fa[300], son[300][2];
inline void up(int& x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%lld%lld%lld%lld%lld%lld%d", &A.a, &A.b, &A.c, &B.a, &B.b, &B.c, &m);
	C = A, D = B;
	for (int i = 0; i <= m; i++, A.up()) {
		if (!M.count(A)) M[A] = ++n;
		if (A.isRoot()) break;
	}
	for (int i = 0; i <= m; i++, B.up()) {
		if (!M.count(B)) M[B] = ++n;
		if (B.isRoot()) break;
	}
	for (std::map<data, int>::iterator it = M.begin(); it != M.end(); it++) {
		if (it->first.isRoot()) continue;
		data x = it->first;
		int way = x.up();
		if (!M.count(x)) continue;
		fa[it->second] = M[x];
		son[M[x]][way] = it->second;
	}
	f[M[C]][0][0] = 1;
	for (int k = 0; k < m; k++) {
		for (int i = 1; i <= n; i++) {
			if (fa[i]) up(f[fa[i]][0][k + 1], f[i][0][k]);
			up(son[i][0] ? f[son[i][0]][0][k + 1] : f[i][1][k + 1], f[i][0][k]);
			up(son[i][1] ? f[son[i][1]][0][k + 1] : f[i][1][k + 1], f[i][0][k]);
			for (int j = 1; j <= m; j++) {
				if (!f[i][j][k]) continue;
				up(f[i][j + 1][k + 1], 1LL * f[i][j][k] * 2 % MOD);
				up(f[i][j - 1][k + 1], f[i][j][k]);
			}
		}
	}
	printf("%d\n", f[M[D]][0][m]);
	return 0;
}
