#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n;
inline int ask(int pos) {
	int x, y;
	printf("? %d\n", pos);
	fflush(stdout);
	scanf("%d", &x);
	printf("? %d\n", pos + n / 2);
	fflush(stdout);
	scanf("%d", &y);
	return x - y;
}
int main() {
	scanf("%d", &n);
	int start = ask(1);
	if (start & 1) return puts("! -1"), 0;
	if (!start) return puts("! 1"), 0;
	int l = 2, r = n / 2;
	while (l <= r) {
		int mid = (l + r) >> 1;
		int val = ask(mid);
		if (!val) return printf("! %d\n", mid), 0;
		if ((val < 0) ^ (start < 0))
			r = mid - 1;
		else
			l = mid + 1;
	}
	return 0;
}