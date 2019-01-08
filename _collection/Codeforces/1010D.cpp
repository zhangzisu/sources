#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
/* type:
 * 1: and
 * 2: or
 * 3: xor
 * 4: not
 * other: in
 */
int n, val[MAXN], type[MAXN], next[MAXN][2], ans[MAXN];
char buf[5];
int pre(int x) {
	switch (type[x]) {
		case 1:
			val[x] = pre(next[x][0]) & pre(next[x][1]);
			break;
		case 2:
			val[x] = pre(next[x][0]) | pre(next[x][1]);
			break;
		case 3:
			val[x] = pre(next[x][0]) ^ pre(next[x][1]);
			break;
		case 4:
			val[x] = !pre(next[x][0]);
			break;
	}
	return val[x];
}
void solve(int x, int v) {
	switch (type[x]) {
		case 1:
			if (val[next[x][0]]) solve(next[x][1], v);
			if (val[next[x][1]]) solve(next[x][0], v);
			break;
		case 2:
			if (!val[next[x][0]]) solve(next[x][1], v);
			if (!val[next[x][1]]) solve(next[x][0], v);
			break;
		case 3:
			solve(next[x][0], v);
			solve(next[x][1], v);
			break;
		case 4:
			solve(next[x][0], v);
			break;
		default:
			ans[x] = v;
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		switch (buf[0]) {
			case 'A':
				type[i] = 1;
				scanf("%d%d", next[i], next[i] + 1);
				break;
			case 'O':
				type[i] = 2;
				scanf("%d%d", next[i], next[i] + 1);
				break;
			case 'X':
				type[i] = 3;
				scanf("%d%d", next[i], next[i] + 1);
				break;
			case 'N':
				type[i] = 4;
				scanf("%d", next[i]);
				break;
			case 'I':
				scanf("%d", val + i);
				break;
		}
	}
	std::fill(ans, ans + n + 1, pre(1));
	solve(1, !ans[0]);
	for (int i = 1; i <= n; i++)
		if (!type[i]) putchar('0' + ans[i]);
	putchar(10);
	return 0;
}