#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define SIGMA 10
#define MAXS 40
struct state {
	int son[SIGMA], link, len;
	inline state(int len = 0) {
		memset(son, 0, sizeof(son));
		this->link = 0;
		this->len = len;
	}
	inline state(state &x, int len) {
		memcpy(son, x.son, sizeof(son));
		this->link = x.link;
		this->len = len;
	}
	inline int &operator[](int index) { return son[index]; }
} sam[MAXS << 1];
int root, pre, cur;
inline void extend(int x) {
	int p, q, s, c;
	sam[p = ++cur] = state(sam[q = pre].len + 1);
	pre = p;
	for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
	if (!q) return void(sam[p].link = root);
	s = sam[q][x];
	if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
	sam[c = ++cur] = state(sam[s], sam[q].len + 1);
	for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
	sam[s].link = sam[p].link = c;
}
inline void reset() { sam[root = pre = cur = 1] = state(); }
int map[100][100];
int main() {
	{
		FILE *fp = fopen("string.list", "r");
		int n, k, ans;
		while (fscanf(fp, "%d%d%d", &n, &k, &ans) == 3) {
			map[n][k] = ans;
		}
		fclose(fp);
	}
	FILE *fp = fopen("string.list", "a");
	const int T = 5;
	for (int n = 1; n <= 2 * T; n++) {
		for (int k = 1; k <= n; k++) {
			if (map[n][k]) continue;
			long long all = 1, ans = 0;
			for (int i = 1; i <= n; i++) all *= k;
			printf("ALL = %lld\n", all);
			for (long long mask = 0; mask < all; mask++) {
				reset();
				for (long long t = mask, i = 1; i <= n; i++, t /= k) extend(t % k);
				ans += cur;
			}
			fprintf(fp, "%d %d %lld\n", n, k, ans % 1000000007);
		}
	}
	return 0;
}