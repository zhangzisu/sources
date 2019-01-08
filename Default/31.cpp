#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <stack>
#include <vector>
#define MAXN 200010
#define MOD1 1000000007
#define MOD2 1000000009
#define BASE 47
int n, q, bin[MAXN], hash1[MAXN], hash2[MAXN], base1[MAXN], base2[MAXN], sa[MAXN], rank[MAXN], ans[MAXN], vis[MAXN];
char buf[MAXN];
inline int calc1(int l, int r) { return (hash1[r] - 1LL * hash1[l - 1] * base1[r - l + 1] % MOD1 + MOD1) % MOD1; }
inline int calc2(int l, int r) { return (hash2[r] - 1LL * hash2[l - 1] * base2[r - l + 1] % MOD2 + MOD2) % MOD2; }
inline int lcp(int a, int b) {
	int l = 1, r = std::min(n - a, n - b) + 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (calc1(a, a + mid - 1) == calc1(b, b + mid - 1) && calc2(a, a + mid - 1) == calc2(b, b + mid - 1)) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return r;
}
inline int cmp(int a, int b) {
	int r = lcp(a, b);
	return buf[a + r] < buf[b + r];
}
std::vector<std::pair<int, int> > query[MAXN];
std::vector<int> rm[MAXN], dep[MAXN];
std::set<int> cnd;
std::stack<int> stk;
void del(int x) {
	if (vis[x]) return;
	vis[x] = 1;
	cnd.erase(x);
	for (std::vector<int>::iterator y = dep[x].begin(); y != dep[x].end(); y++) del(*y);
}
inline int $() {
	register int x = 0;
	register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
	return x;
}
int main() {
	scanf("%s", buf + 1);
	q = $();
	n = strlen(buf + 1);
	base1[0] = base2[0] = 1;
	bin[0] = -1;
	for (int i = 1; i <= n; i++) {
		hash1[i] = (1LL * hash1[i - 1] * BASE + buf[i]) % MOD1;
		hash2[i] = (1LL * hash2[i - 1] * BASE + buf[i]) % MOD2;
		base1[i] = 1LL * base1[i - 1] * BASE % MOD1;
		base2[i] = 1LL * base2[i - 1] * BASE % MOD2;
		sa[i] = i;
		bin[i] = bin[i >> 1] + 1;
	}
	std::sort(sa + 1, sa + n + 1, cmp);
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	for (int i = 1, l, r; i <= q; i++) {
		l = $(), r = $();
		query[r].push_back(std::make_pair(l, i));
	}
	for (int i = 1; i <= n; i++) {
		for (; stk.size() && rank[stk.top()] < rank[i]; stk.pop()) {
			rm[i + lcp(i, stk.top())].push_back(stk.top());
			dep[i].push_back(stk.top());
		}
		for (std::vector<int>::iterator j = rm[i].begin(); j != rm[i].end(); j++) del(*j);
		stk.push(i);
		cnd.insert(i);
		for (std::vector<std::pair<int, int> >::iterator j = query[i].begin(); j != query[i].end(); j++) ans[j->second] = *cnd.lower_bound(j->first);
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}