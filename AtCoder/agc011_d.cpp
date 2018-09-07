#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#define MAXN 200010
int n, k, p, a[MAXN];
char buf[MAXN], ans[2][MAXN];
std::deque<int> Q;
int main() {
	scanf("%d%d%s", &n, &k, buf + 1);
	for (int i = 1; i <= n; i++) Q.push_back(buf[i] == 'B');
	for (int i = 1; i <= 2 * n + 2; i++) {
		if (Q.front() ^ p) {
			Q.pop_front();
			p ^= 1;
			Q.push_back(p);
		} else {
			Q.pop_front();
			Q.push_front(p ^ 1);
		}
		if (i == k) {
			for (int j = 1; j <= n; j++) printf("%c", (Q[j - 1] ^ p) + 'A');
			puts("");
			return 0;
		}
		if (i > 2 * n) {
			for (int j = 1; j <= n; j++) ans[i - 2 * n - 1][j] = (Q[j - 1] ^ p) + 'A';
		}
	}
	puts(ans[~k & 1] + 1);
	return 0;
}