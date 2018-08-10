#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 1010
const int INF = 0x3F3F3F3F;
int n, m, q, h[MAXN][MAXN], f[MAXN][MAXN];
std::vector<std::pair<int, std::pair<int, int> > > V;
inline void up(int &x, int y){
	if(y > x)x = y;
}
int main(){
	freopen("nagame.in", "r", stdin);
	freopen("nagame.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d", &h[i][j]), V.push_back(std::make_pair(-h[i][j], std::make_pair(i, j)));
		}
	}
	std::sort(V.begin(), V.end());
	for(int i = 0;i < (int)V.size();i++){
		int x = V[i].second.first;
		int y = V[i].second.second;
		if(x > 1 && h[x - 1][y] >= h[x][y]){
			if(h[x - 1][y] > h[x][y]){
				up(f[x][y], f[x - 1][y] + 1);
			}else{
				up(f[x][y], INF);
			}
		}
		if(x < n && h[x + 1][y] >= h[x][y]){
			if(h[x + 1][y] > h[x][y]){
				up(f[x][y], f[x + 1][y] + 1);
			}else{
				up(f[x][y], INF);
			}
		}
		if(y > 1 && h[x][y - 1] >= h[x][y]){
			if(h[x][y - 1] > h[x][y]){
				up(f[x][y], f[x][y - 1] + 1);
			}else{
				up(f[x][y], INF);
			}
		}
		if(y < m && h[x][y + 1] >= h[x][y]){
			if(h[x][y + 1] > h[x][y]){
				up(f[x][y], f[x][y + 1] + 1);
			}else{
				up(f[x][y], INF);
			}
		}
//		printf("f[%d][%d] = %d\n", x, y, f[x][y]);
	}
	scanf("%d", &q);
	for(int x, y, z;q;q--){
		scanf("%d%d%d", &x, &y, &z);
		puts(f[x][y] >= z ? "= =" : "> <");
	} 
	return 0;
}
