#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int a[3], b[3];
int main() {
	freopen("mixmilk.in", "r", stdin);
	freopen("mixmilk.out", "w", stdout);
	for (int i = 0; i < 3; i++) scanf("%d%d", &a[i], &b[i]);
	for (int i = 0; i < 100; i++) {
		int now = i % 3, nxt = (i + 1) % 3;
		int delta = std::min(a[nxt] - b[nxt], b[now]);
		b[now] -= delta;
		b[nxt] += delta;
	}
	printf("%d\n%d\n%d\n", b[0], b[1], b[2]);
	return 0;
}