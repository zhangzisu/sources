#include<cmath>
#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline int $1(){
	register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	return ch ^ 48;
}
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#define MAXN 40
std::queue<std::pair<int, int> > Q;
int n = $(), m = $(), t = $(), f[MAXN][MAXN], g[MAXN][MAXN], inq[MAXN][MAXN];
inline void spfa(int sx, int sy){
	Q.push(std::make_pair(sx, sy));
	memset(g, 0x3F, sizeof(g));
	g[sx][sy] = f[sx][sy];inq[sx][sy] = 1;
	while(!Q.empty()){
		int x = Q.front().first, y = Q.front().second;Q.pop();
		inq[x][y] = 0;
		if(x > 1 && g[x - 1][y] > g[x][y] + f[x - 1][y]){
			g[x - 1][y] = g[x][y] + f[x - 1][y];
			if(!inq[x - 1][y])inq[x - 1][y] = 1, Q.push(std::make_pair(x - 1, y));
		}
		if(x < n && g[x + 1][y] > g[x][y] + f[x + 1][y]){
			g[x + 1][y] = g[x][y] + f[x + 1][y];
			if(!inq[x + 1][y])inq[x + 1][y] = 1, Q.push(std::make_pair(x + 1, y));
		}
		if(y > 1 && g[x][y - 1] > g[x][y] + f[x][y - 1]){
			g[x][y - 1] = g[x][y] + f[x][y - 1];
			if(!inq[x][y - 1])inq[x][y - 1] = 1, Q.push(std::make_pair(x, y - 1));
		}
		if(y < n && g[x][y + 1] > g[x][y] + f[x][y + 1]){
			g[x][y + 1] = g[x][y] + f[x][y + 1];
			if(!inq[x][y + 1])inq[x][y + 1] = 1, Q.push(std::make_pair(x, y + 1));
		}
	}
}
inline double dis(double x1, double y1, double x2, double y2){
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double ans = 0;
int main(){
	for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)f[i][j] = $1();
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++){
			spfa(i, j);
			for(int k = 1;k <= n;k++)
				for(int l = 1;l <= m;l++)
					if(g[k][l] <= t)
						ans = std::max(ans, dis(i, j, k, l));
		}
	printf("%.6f\n", ans);
	return 0;
}
