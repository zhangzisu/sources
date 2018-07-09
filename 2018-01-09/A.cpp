#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
#define MOD 1000003
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline void $(int &x, int y){
	x += y;
	if(x >= MOD)x -= MOD;
}
#define MAXN 5010
int n = $(), m = $(), k = $(), ans = 0;
bool dd[MAXN][MAXN];
int s[MAXN][MAXN];
long long frc[MAXN], inv[MAXN];
inline long long fpow(long long x, int p){
	long long ret = 1;
	while(p){
		if(p & 1)(ret *= x) %= MOD;
		(x *= x) %= MOD;
		p >>= 1;
	}
	return ret;
}
inline long long C(int n, int m){return frc[n] * inv[m] % MOD * inv[n - m] % MOD;}
int main(){
	frc[0] = 1;
	for(int i = 1;i < MAXN;i++)frc[i] = frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
	for(int i = MAXN - 1;i;i--)inv[i - 1] = inv[i] * i % MOD;
	
	for(int i = 1;i <= k;i++){
		int x = $(), y = $();
		dd[n - x + 1][m - y + 1] = 1;
	}
	for(int i = 0;i <= m;i++)s[0][i] = 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			$(s[i][j], s[i][j - 1] + (dd[i][j] ? 0 : s[i - 1][j - 1]));
	puts("TABLE:");
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++)printf("%5d", s[i][j]);
		puts("");
	}
	printf("%d\n", s[n][m]);
	return 0;
}
