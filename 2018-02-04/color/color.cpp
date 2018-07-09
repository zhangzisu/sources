#include<cstdio>
#include<cctype>
inline long long $(){
	register long long x = 0, f = 0; register char ch = getchar();
	while(!isdigit(ch) && (ch ^ 45))ch = getchar();
	if(!(ch ^ 45))ch = getchar(), f = 1;
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#define MOD 1000000007
#define MAXN 17
int n, map[MAXN][MAXN], avia[1 << MAXN], f[1 << MAXN], g[1 << MAXN];
inline long long frc(int x){
	long long ret = 1;
	for(int i = 2;i <= x;i++)(ret *= i) %= MOD;
	return ret;
}
int main(){
	#ifndef DEBUG
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	#endif
	n = $();
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			map[i][j] = $();
	for(int i = 0;i < (1 << n);i++){
		avia[i] = 1;
		for(int j = 0;j < n;j++)if((i >> j) & 1)
			for(int k = 0;k < n;k++)if((i >> k) & 1)
				if(map[j][k]) { avia[i] = 0; goto fail; }
		fail:;
	}
	memset(f, 0x3F, sizeof(f));f[0] = 0;g[0] = 1;
	for(int d = 0;d < (1 << n);d++){
		int mask = d ^ ((1 << n) - 1);
		for(int next = mask;next;next = (next - 1) & mask){
			if(avia[next]){
				if(f[d] + 1 == f[next | d]){
					(g[next | d] += g[d]) %= MOD;
				}else if(f[d] + 1 < f[next | d]){
					g[next | d] = g[d];
					f[next | d] = f[d] + 1;
				}
			};
		}
	}
	printf("%d %d\n", f[(1 << n) - 1], g[(1 << n) - 1]);
	return 0;
}