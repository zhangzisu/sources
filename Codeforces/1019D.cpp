#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
typedef long long lnt;
int n;
lnt s;
struct point_t {
	int x, y;
} points[MAXN];
int main() {
	scanf("%d%lld", &n, &s);
	for (int i = 1; i <= n; i++) scanf("%d%d", &points[i].x, &points[i].y);
	//
	return 0;
}