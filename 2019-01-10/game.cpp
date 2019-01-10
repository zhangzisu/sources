#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000010
int son[MAXN][26], cnt;
inline void insert(const char *s) {
	int p = 1;
	for (; *s; s++) {
		int &x = son[p][*s - 'a'];
		if (!x) {
			x = ++cnt;
			memset(son[x], 0, sizeof(son[x]));
		}
		p = x;
	}
}
int sg[MAXN];
void dp(int x) {
	int tmp[27];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < 26; i++) {
		if (son[x][i]) {
			dp(son[x][i]);
			tmp[sg[son[x][i]]] = 1;
		}
	}
	for (int i = 0; i <= 26; i++) {
		if (!tmp[i]) {
			sg[x] = i;
			break;
		}
	}
}
int T, n, m;
char buf[MAXN];
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	for (scanf("%d", &T); T; T--) {
		scanf("%s%d", buf + 1, &m);
		n = strlen(buf + 1);
		cnt = 1;
		memset(son[1], 0, sizeof(son[1]));
		for (int i = 1; i <= n; i++) insert(buf + i);
		dp(1);
		int ans = 0;
		for (int i = 1, l, r; i <= m; i++) {
			scanf("%d%d", &l, &r);
			int p = 1;
			for (int j = l; j <= r; j++) p = son[p][buf[j] - 'a'];
			ans ^= sg[p];
		}
		puts(ans ? "Alice" : "Bob");
	}
}