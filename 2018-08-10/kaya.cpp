#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int n;
struct point{
	int x, y, id;
	inline friend bool operator < (point a, point b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
}p[100010];
int main(){
	freopen("kaya.in", "r", stdin);
	freopen("kaya.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1;i <= n;i++) scanf("%d%d", &p[i].x, &p[i].y), p[i].id = i;
	std::sort(p + 1, p + n + 1);
	printf("%d %d %d %d %d %d\n", p[1].id, p[2].id, p[3].id, p[n - 2].id, p[n - 1].id, p[n].id);
	return 0;
}
