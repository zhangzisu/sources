#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
typedef long long lnt;
int n, m;
std::map<int, lnt> M;
lnt ans = 0, tmp = 0;
lnt p = 1, q = 0;
inline lnt sum() { return q * n + p * n * (n + 1) / 2; }
inline lnt val(int x) { return p * x + q; }
char buf[50];
int main() {
	scanf("%d%d", &n, &m);
	for (int x, y; m; m--) {
		scanf("%s%d%d", buf, &x, &y);
		if (buf[0] == 'A') {
			p = x;
			q = y;
			M.clear();
			tmp = 0;
		} else {
			if (M.count(x))
				tmp -= M[x];
			else
				tmp -= val(x);
			tmp += y;
			M[x] = y;
		}
		printf("%lld\n", sum() + tmp);
	}
	return 0;
}
