#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 110
int n, m, k;
int a[MAXN][2], s[MAXN][2], f[MAXN][MAXN][MAXN];
int main(){
	scanf("%d%d%d", &n, &m, &k);
	if(m == 1){
		int a[MAXN], s[MAXN], f[MAXN][MAXN];
		memset(a, 0, sizeof(a));
		memset(s, 0, sizeof(s));
		memset(f, 0, sizeof(f));
		for(int i = 1;i <= n;i++)scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
		for(int i = 0;i <= n;i++)for(int j = 1;j <= k;j++)f[i][j] = -0x3F3F3F3F;
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= k;j++){
				f[i][j] = f[i - 1][j];
				for(int l = 0;l < i;l++)f[i][j] = std::max(f[i][j], f[l][j - 1] + s[i] - s[l]);
			}
		}
		printf("%d\n", f[n][k]);
		return 0;
	}
	for(int i = 1;i <= n;i++){
		scanf("%d%d", &a[i][0], &a[i][1]);
		s[i][0] = s[i - 1][0] + a[i][0];
		s[i][1] = s[i - 1][1] + a[i][1];
	}
	for(int i = 0;i <= n;i++)for(int j = 0;j <= n;j++)for(int l = 1;l <= k;l++)f[i][j][l] = -0x3F3F3F3F;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++){
			for(int l = 1;l <= k;l++){
				f[i][j][l] = std::max(f[i - 1][j][l], f[i][j - 1][l]);
				for(int o = 0;o < i;o++)f[i][j][l] = std::max(f[i][j][l], f[o][j][l - 1] + s[i][0] - s[o][0]);
				for(int o = 0;o < j;o++)f[i][j][l] = std::max(f[i][j][l], f[i][o][l - 1] + s[j][1] - s[o][1]);
				if(i == j){
					for(int o = 0;o < i;o++)f[i][j][l] = std::max(f[i][j][l], f[o][o][l - 1] + s[i][0] + s[i][1] - s[o][0] - s[o][1]);
				}
			}
		}
	printf("%d\n", f[n][n][k]);
	return 0;
}
