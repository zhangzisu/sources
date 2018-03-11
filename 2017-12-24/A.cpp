#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline long long $(){
	register long long x = 0, f = 0;register char ch = gc();
	while(!isdigit(ch) && (ch ^ 45))ch = gc();
	if(!(ch ^ 45))ch = gc(), f = 1;
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#define MAXN 3000
#define MOD 1000000007
long long a[MAXN], b[MAXN], c[MAXN], n = $(), N = 0, q = $();
long long f[MAXN][MAXN], dt = 1, frc[MAXN], inv[MAXN];
inline long long fpow(long long x, long long p){
	register long long ret = 1;
	while(p){
		if(p & 1)ret = (ret * x) % MOD;
		x = (x * x) % MOD;
		p >>= 1;
	}
	return ret;
}
inline long long C(long long n, long long m){
	return frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int main(){
	frc[0] = 1;
	for(int i = 1;i < MAXN;i++)frc[i] = frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
	for(int i = MAXN - 1;i;i--)inv[i - 1] = inv[i] * i % MOD;
	
	for(int i = 1;i <= n;i++)c[a[i] = $() % q]++;
	for(int i = 0;i < q;i++)if(c[i])b[++N] = c[i], (dt *= frc[c[i]]) %= MOD;
	c[0] = 1;
	for(int i = 1;i <= N;i++)c[i] = c[i - 1] + b[i];
	
	f[0][0] = 1;
	for(int i = 1;i <= N;i++){
		for(int j = 0;j <= c[i - 1];j++){
			if(!f[i - 1][j])continue;
			for(int k = 0;k <= j;k++){
				for(int l = 0;l <= c[i - 1] - j && l + k <= b[i];l++){
					if(l + k){
						(f[i][j + b[i] - k - k - l] +=
							f[i - 1][j] * C(j, k) % MOD *
							C(c[i - 1] - j, l) % MOD *
							C(b[i] - 1, k + l - 1) % MOD) %= MOD;
					}
				}
			}
		}
	}
	printf("%lld\n", f[N][0] * dt % MOD);
	return 0;
}
