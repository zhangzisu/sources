#include<cstdio>
#include<cstdlib>
#define MAXN 1010
long long f[MAXN][MAXN], n, m;
int main(){
	scanf("%lld%lld", &m, &n);
	for(int i = 0;i <= n;i++)f[i][0] = 1;
	for(int i = 1;i <= m;i++)f[0][i] = 2;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			f[i][j] = f[i][j - 1] + f[i - 1][j - 1];
		}
	}
	printf("%lld\n", f[n][m]);
	return 0;
}
