#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <vector>
#define MAXN 100010
typedef long long lnt;
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int fa[MAXN], top[MAXN], size[MAXN], deep[MAXN];
void pre(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		pre(to[i]);
		size[x] += size[to[i]];
	}
}
void split(int x) {
	int max = 0;
	if (!top[x]) top[x] = x;
	for (int i = head[x]; ~i; i = next[i])
		if (size[to[i]] > size[max]) max = to[i];
	if (max) top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != max) split(to[i]);
}
int n, c[MAXN], id[MAXN];
std::stack<std::pair<int, int>> s[MAXN];
int bit[MAXN], tim[MAXN], ts;
inline void clear() { ++ts; }
inline int lowbit(int x) { return x & -x; }
inline void add(int n, int x, int y) {
	for (; x <= n; x += lowbit(x)) {
		if (tim[x] == ts) {
			bit[x] += y;
		} else {
			bit[x] = y;
			tim[x] = ts;
		}
	}
}
inline int qry(int n, int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) {
		if (tim[x] == ts) y += bit[x];
	}
	return y;
}
std::vector<int> val;
std::vector<std::pair<int, int>> all, tmp;
inline lnt calc(const std::vector<std::pair<int, int>> &v) {
	val.clear();
	for (auto x : v) val.push_back(x.first);
	std::sort(val.begin(), val.end());
	val.erase(std::unique(val.begin(), val.end()), val.end());
	lnt ret = 0;
	clear();
	for (auto x : v) {
		int p = std::lower_bound(val.begin(), val.end(), x.first) - val.begin() + 1;
		ret += x.second * qry((int)val.size(), p - 1);
		add((int)val.size(), p, x.second);
	}
	return ret;
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", c + i);
	id[1] = 1;
	for (int i = 2, u, v; i <= n; i++) {
		scanf("%d%d", &u, &v);
		$(u, v);
		id[i] = v;
	}
	pre(1);
	split(1);
	s[top[1]].emplace(c[1], 1);
	for (int i = 2; i <= n; i++) {
		all.clear();
		for (int x = id[i]; x; x = fa[top[x]]) {
			std::stack<std::pair<int, int>> &s = ::s[top[x]];
			int len = deep[x] - deep[top[x]] + 1;
			tmp.clear();
			while (s.size() && s.top().second <= len) {
				tmp.push_back(s.top());
				len -= s.top().second;
				s.pop();
			}
			if (s.size() && len) {
				auto last = s.top();
				s.pop();
				tmp.emplace_back(last.first, len);
				s.emplace(last.first, last.second - len);
			}
			s.emplace(c[id[i]], deep[x] - deep[top[x]] + 1);
			all.insert(all.end(), tmp.rbegin(), tmp.rend());
		}
		printf("%lld\n", calc(all));
	}
	return 0;
}