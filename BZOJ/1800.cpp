#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
int n, a[30], ans;
inline int calc(int x, int y){
	register int ret = 0;
	while(x != y){
		ret += a[x++];
		if(x > n)x = 1;
	}
	return ret;
}
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
	for(int i = 1;i <= n;i++)
		for(int j = i + 1;j <= n;j++)
			for(int k = j + 1;k <= n;k++)
				for(int l = k + 1;l <= n;l++)
					if(calc(i, j) == calc(k, l) && calc(j, k) == calc(l, i))ans++;
	printf("%d\n", ans);
	return 0;
}
