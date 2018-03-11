#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 12
#define INF 0x3F3F3F3F
int n = $(), m = $(), f[MAXN][MAXN], d[MAXN], g[1 << MAXN], ans = INF;
void $(int x){
	if(x == (1 << n) - 1)ans = std::min(ans, g[x]);
	for(int i = 0;i < n;i++){
		if((x >> i) & 1){
			for(int j = 0;j < n;j++){
				if(!((x >> j) & 1) && f[i][j] != INF && g[x | (1 << j)] > g[x] + f[i][j] * d[i]){
					int bk = d[j];d[j] = d[i] + 1;
					g[x | (1 << j)] = g[x] + f[i][j] * d[i];
					$(x | (1 << j));
					d[j] = bk;
				}
			}
		}
	}
}
int main(){
	memset(f, 0x3F, sizeof(f));
	for(int i = 0;i < m;i++){
		int $1 = $() - 1, $2 = $() - 1, $3 = $();
		if($3 < f[$1][$2])f[$1][$2] = f[$2][$1] = $3;
	}
	for(int i = 0;i < n;i++){
		memset(d, 0x3F, sizeof(d));
		memset(g, 0x3F, sizeof(g));
		d[i] = 1;g[1 << i] = 0;
		$(1 << i);
	}
	printf("%d\n", ans);
	return 0;
} 
