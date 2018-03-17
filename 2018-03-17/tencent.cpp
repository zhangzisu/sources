#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 110
#define MOD 1000000007
#define _ long long
_ n, m, a[MAXN], ans;
_ C[MAXN];
void prepare(int n){
	if(!n){
		//
	}else{
		//
	}
}
int main(){
#ifndef DEBUG
	freopen("tencent.in" , "r", stdin );
	freopen("tencent.out", "w", stdout);
#endif
	frc[0] = 1;
	for(_ i = 1;i < MAXN;i++)frc[i] = frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for(_ i = MAXN - 1;i;i--)inv[i - 1] = inv[i] * i % MOD;

	scanf("%lld%lld%*d", &n, &m);
	for(_ i = 1;i <= n;i++)scanf("%lld", &a[i]);
	for(_ i = 1;i <= n;i++){
		sx[i] = -a[i]; sy[i] = a[i];
		ex[i] = a[n - i +  1];
		ey[i] = m - a[n - i + 1];
	}
	if(n == 2){
		ans = calc(sx[1], sy[1], ex[1], ey[1]) * calc(sx[2], sy[2], ex[2], ey[2]) % MOD;
		ans -= calc(sx[1], sy[1], ex[2], ey[2]) * calc(sx[2], sy[2], ex[1], ey[1]) % MOD;
		((ans %= MOD) += MOD) %= MOD;
	}else{
		ans = (_)"FUCK!";
	}
	printf("%lld\n", ans);
#ifndef DEBUG
	fclose(stdin);
	fclose(stdout);
#endif
}
