#include<cstdio>
#include<algorithm>
#define MAXN 100010
int n, k, a1[MAXN], a2[MAXN], a3[MAXN << 1], a4[MAXN << 1], *a5 = a3 + MAXN;
int main(){
	freopen("TRAKTOR.IN", "r", stdin);
	freopen("TRAKTOR.OUT", "w", stdout);

	scanf("%d%d", &n, &k);
	for(int i = 1, x, y;i <= n;i++){
		scanf("%d%d", &x, &y);
		if(++a1[x] >= k)return printf("%d\n", i), 0;
		if(++a2[y] >= k)return printf("%d\n", i), 0;
		if(++a5[x - y] >= k)return printf("%d\n", i), 0;
		if(++a4[x + y] >= k)return printf("%d\n", i), 0;
	}
	puts("-1");
}