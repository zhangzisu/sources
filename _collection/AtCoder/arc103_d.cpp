#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
int n;
lnt d[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &d[i]);
	std::sort(d + 1, d + n + 1);
	for (int i = n; i >= 1; i--) {
		//
	}
	return 0;
}