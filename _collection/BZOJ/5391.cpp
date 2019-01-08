#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
char buf[MAXN];
int cnt[26], ans = MAXN;
int main() {
	scanf("%s", buf);
	for (char *s = buf; *s; s++) cnt[*s - 'a']++;
	for (int i = 0; i < 26; i++) ans = std::min(ans, cnt[i]);
	printf("%d\n", ans);
	return 0;
}