#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 410
char _orz[MAXN], _fsb[MAXN], _sro[10][MAXN];
int orz[MAXN], fsb[MAXN], sro[10][MAXN];
int n, m, k, len[10], next[MAXN][2], f[MAXN][MAXN][1<<8];
int ans = 0x3F3F3F3F;
inline void up(int &x, int y){if(y < x)x = y;}
int main(){
	scanf("%s%s%d", _orz + 1, _fsb + 1, &n);
	m = strlen(_orz + 1);k = strlen(_fsb + 1);
	for(int i = 0;i < n;i++)scanf("%s", _sro[i] + 1), len[i] = strlen(_sro[i] + 1);
	for(int i = 1;i <= m;i++)orz[i] = _orz[i] == 'a';
	for(int i = 1;i <= k;i++)fsb[i] = _fsb[i] == 'a';
	for(int i = 0;i < n;i++)for(int j = 1;j <= len[i];j++)sro[i][j] = _sro[i][j] == 'a';
	for(int i = m;i;i--){
		next[i][0] = next[i + 1][0];
		next[i][1] = next[i + 1][1];
		next[i][orz[i]] = i;
	}
	memset(f, 0x3F, sizeof(f));
	f[0][0][0] = 0;
	for(int i = 0;i < m;i++){
		for(int j = 0;j < k;j++){
			for(int l = 0;l < (1 << n);l++){
				if(f[i][j][l] == 0x3F3F3F3F)continue;
				if(next[i + 1][fsb[j + 1]]){
					up(f[next[i + 1][fsb[j + 1]]][j + 1][l],
					   f[i][j][l] + next[i + 1][fsb[j + 1]] - i - 1);
					//printf("\tf[%d][%d][%d]=%d\n", next[i + 1][fsb[j + 1]], j + 1, l, f[next[i + 1][fsb[j + 1]]][j + 1][l]);
				}
				for(int x = 0;x < n;x++){
					if(!((l >> x) & 1)){
						for(int y = 1;y <= len[x] && j + y <= k;y++)
							if(fsb[j + y] == sro[x][y])
								up(f[i][j + y][l | (1 << x)],
								   f[i][j][l] + len[x] - y);
							else break;
					}
				}
			}
		}
	}
	for(int i = 0;i <= m;i++)for(int j = 0;j < (1 << n);j++)up(ans, f[i][k][j] + m - i);
	printf("%d\n", ans);
	return 0;
}
