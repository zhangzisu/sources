#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
inline int $() {
	register int x = 0;
	register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 2010
int n, G[MAXN][MAXN], MG[MAXN][MAXN], d[MAXN];
int dfn[MAXN], low[MAXN], ins[MAXN], stk[MAXN], scc[MAXN], snt, top, dfsclk;
std::vector<int> p[MAXN], s;
int next[MAXN];
void zzs(int x) {
	dfn[x] = low[x] = ++dfsclk;
	ins[stk[++top] = x] = 1;
	for (int y = 1; y <= n; y++) {
		if (G[x][y]) {
			if (dfn[y]) {
				if (ins[y]) low[x] = std::min(low[x], dfn[y]);
			} else {
				zzs(y);
				low[x] = std::min(low[x], low[y]);
			}
		}
	}
	if (low[x] == dfn[x]) {
		++snt;
		do {
			p[snt].push_back(stk[top]);
			ins[stk[top]] = 0;
			scc[stk[top]] = snt;
		} while (stk[top--] != x);
	}
}
inline void get(int sid) {
	int head, tail;
	head = tail = p[sid][0];
	if ((int)p[sid].size() == 1) return next[head] = head, void();
	for (int i = 1; i < (int)p[sid].size(); i++) {
		int x = p[sid][i];
		if (G[x][head]) {
			next[x] = head;
			head = x;
			continue;
		}
		if (G[tail][x]) {
			next[tail] = x;
			tail = x;
			continue;
		}
		for (int a = head, b = next[head]; b; a = b, b = next[b]) {
			if (G[x][b]) {
				next[a] = x;
				next[x] = b;
				break;
			}
		}
	}
	tail = head;
	head = 0;
	for (int x = next[tail]; x; x = next[x]) {
		if (head) {
			for (int a = tail, b = head;; a = b, b = next[b]) {
				if (G[x][b]) {
					next[a] = next[tail];
					if (a != tail) next[tail] = head;
					tail = x;
					head = b;
					break;
				}
				if (b == tail) break;
			}
		} else if (G[x][tail]) {
			head = tail, tail = x;
		}
	}
	next[tail] = head;
}
std::queue<int> Q;
int pre[MAXN], dp[MAXN];
void print(int x) {
	printf("%d ", x);
	for (int i = next[x]; i != x; i = next[i]) printf("%d ", i);
	if (pre[scc[x]]) return print(p[pre[scc[x]]][0]);
	puts("");
}
int main() {
	n = $();
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			G[i][j] = (G[j][i] = $()) ^ 1;
		}
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) zzs(i);
	for (int i = 1; i <= snt; i++) get(i);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (scc[i] != scc[j]) MG[scc[i]][scc[j]] |= G[i][j];
		}
	}
	for (int i = 1; i <= snt; i++) {
		for (int j = 1; j <= snt; j++) {
			if (MG[i][j]) d[j]++;
		}
	}
	for (int i = 1; i <= snt; i++)
		if (!d[i]) Q.push(i);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		s.push_back(x);
		for (int i = 1; i <= snt; i++)
			if (MG[x][i] && d[i] && --d[i] == 0) Q.push(i);
	}
	for (int i = (int)s.size() - 1; ~i; i--) {
		int x = s[i];
		for (int y = 1; y <= snt; y++) {
			if (MG[x][y]) {
				if (dp[y] > dp[x]) {
					dp[x] = dp[y];
					pre[x] = y;
				}
			}
		}
		dp[x] += p[x].size();
	}
	for (int i = 1; i <= n; i++) printf("%d ", dp[scc[i]]), print(i);
	return 0;
}