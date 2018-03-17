#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int d[2][2], n, k, w[10000], ans[1 << 18];
inline int calc(int x, int y){
	x &= ((1 << k) - 1);
	y &= ((1 << k) - 1);
	int ret = 0;
	for(int i = 0;i < k;i++)ret |= d[(x>>i)&1][(y>>i)&1] << i;
	return ret;
}
int main(){
	scanf("%d%d%d%d", &d[0][0], &d[0][1], &d[1][0], &d[1][1]);
	scanf("%d%d" ,&n, &k);
	for(int i = 1;i <= n;i++)scanf("%d", &w[i]);
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++){
			if(i == j)continue;
			ans[calc(w[i], w[j])]++;
		}
	
	for(int d = 0; d < (1 << k);d++)printf("%d\n", ans[d]);
}
