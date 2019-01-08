#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
char buf[MAXN];
int main() {
	scanf("%s", buf + 1);
	int n = strlen(buf + 1), s = 1, t;
	while (s < n && buf[s + 1] == buf[s]) s++;
	t = s;
	while (t < n && buf[t + 1] != buf[t]) t++;
	printf("%d\n", t - s + 1);
	return 0;
}