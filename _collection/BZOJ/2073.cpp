#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 16
int m, n, t[MAXN], w[MAXN], f[1 << MAXN], T[1 << MAXN], W[1 << MAXN];
int main(){
	scanf("%d%d", &m, &n);
	memset(f, 0x3F, sizeof(f));
	for(int i = 0;i < n;i++)scanf("%d%d", &t[i], &w[i]);
	for(int i = 0;i < (1 << n);i++)
		for(int j = 0;j < n;j++)
			if((i >> j) & 1)T[i] = std::max(T[i], t[j]), W[i] += w[j];
	f[0] = 0;
	for(int i = 1;i < (1 << n);i++)
		for(int j = i;j;j = i & (j - 1))
			if(W[j] <= m)
				f[i] = std::min(f[i], T[j] + f[i ^ j]);
	printf("%d\n", f[(1 << n) - 1]);
	return 0;
}
