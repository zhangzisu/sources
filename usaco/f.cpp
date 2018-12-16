#include <cctype>
#include <cstdio>
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
const int N = 101;
int n, k, t, a[N][11], vis[N][11];
inline bool check(const int &x, const int &y) {
	return 1 <= x && x <= n && 1 <= y && y <= 10;
}
int size(const int &x, const int &y, const int &t) {
	vis[x][y] = t;
	int ret = 1;
	for (int i = 0; i < 4; i++) {
		const int nx = x + dx[i], ny = y + dy[i];
		if (!check(nx, ny)) continue;
		if (vis[nx][ny] == t) continue;
		if (a[nx][ny] != a[x][y]) continue;
		ret += size(nx, ny, t);
	}
	return ret;
}
void clear(const int &x, const int &y, const int &t) {
	vis[x][y] = t;
	for (int i = 0; i < 4; i++) {
		const int nx = x + dx[i], ny = y + dy[i];
		if (!check(nx, ny)) continue;
		if (vis[nx][ny] == t) continue;
		if (a[nx][ny] != a[x][y]) continue;
		clear(nx, ny, t);
	}
	a[x][y] = 0;
}
inline void drop() {
	for (int j = 1; j <= 10; j++) {
		for (int i = n, k = 0; i >= 1; i--) {
			k += !a[i][j];
			if (a[i][j]) {
				a[i + k][j] = a[i][j];
				if (k != 0) a[i][j] = 0;
			}
		}
	}
}
inline bool solve() {
	t++;
	bool flag = false;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 10; j++) {
			if (vis[i][j] == t || !a[i][j]) continue;
			if (size(i, j, t) >= k) {
				clear(i, j, t + 1);
				flag = true;
			}
		}
	}
	t++;
	drop();
	return flag;
}
int main() {
	freopen("mooyomooyo.in", "r", stdin);
	freopen("mooyomooyo.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 10; j++) {
			scanf("%1d", &a[i][j]);
		}
	}
	for (;;)
		if (!solve())
			break;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 10; j++) {
			printf("%d", a[i][j]);
		}
		puts("");
	}
	return 0;
}