#include<cstdio>
#include<cctype>
#define BUF 1024768
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $() {
	register int x = 0; register char ch = gc();
	while (!isdigit(ch))ch = gc();
	for (; isdigit(ch); ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MOD 1000000007
#define MAXN 5010
int n, m, a[MAXN];
inline long long fpow(long long x, int p){
	register long long ret = 1;
	while(p){
		if(p & 1)ret = ret * x % MOD;
		x = x * x % MOD;
		p >>= 1;
	}
	return ret;
}
long long frc[MAXN], inv[MAXN], ans;
inline long long C(int n, int m){return frc[n] * inv[m] % MOD * inv[n - m] % MOD;}
inline long long D(int n, int m){return m > 0 ? C(n + m - 1, m - 1) : 0;}
int main(){
	frc[0] = 1;
	for(int i = 1;i < MAXN;i++)frc[i] = frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
	for(int i = MAXN - 1;i;i--)inv[i - 1] = inv[i] * i % MOD;
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= m;i++)scanf("%d", &a[i]);
	for(int i = 0;i <= n;i++){
		long long tmp = C(n, i);
		for(int j = 1;j <= m;j++)(tmp *= D(a[j], n - i)) %= MOD;
		(((ans += ((i & 1) ? -1 : 1) * tmp) %= MOD) += MOD) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}
