#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
lnt n, ans;
int a[100], top = 0;
int main() {
	scanf("%lld", &n);
	while (n) a[++top] = n % 10, n /= 10;
	for (int i = 1; i <= top; i++) {
		if (a[i] == 9) {
			ans += 9;
			continue;
		}
		int pos = i;
		for (int j = i + 1; j <= top; j++)
			if (a[j]) {
				pos = j;
				break;
			}
		if (pos != i) {
			for (int j = i + 1; j < pos; j++) a[j] = 9;
			a[pos]--;
			ans += a[i] + 10;
		} else {
			ans += a[i];
		}
	}
	printf("%lld\n", ans);
	return 0;
}