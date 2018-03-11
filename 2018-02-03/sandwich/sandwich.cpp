#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;
	register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline char _(){
	register char ch = getchar();
	while(!isalpha(ch))ch = getchar();
	return ch;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 410
int type[MAXN][MAXN], vis[MAXN][MAXN], res[MAXN][MAXN], n, m, ans;
void dfs(int x, int y, int d){
	if(x < 1 || y < 1 || x > n || y > m)return;
	if(!~vis[x][y])return void(ans = 0x3F3F3F3F);
	if(vis[x][y])return;
	ans += 2; vis[x][y] = -1;
	if (type[x][y])
		if(d == 1 || d == 2)dfs(x, y - 1, 2), dfs(x + 1, y, 1);
		else dfs(x, y + 1, 4), dfs(x - 1, y, 3);
	else
		if(d == 1 || d == 4)dfs(x, y + 1, 4), dfs(x + 1, y, 1);
		else dfs(x, y - 1, 2), dfs(x - 1, y, 3);
	vis[x][y] = 1;
}

inline void init(){
	n = $(); m = $();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			type[i][j] = _() == 'N';
		}
	}
	for(int i = 1;i <= n;i++){
		memset(vis, 0, sizeof(vis)); ans = 0;
		for(int j = 1;j <= m;j++){
			dfs(i, j, 2);
			res[i][j] = ans;
		}
	}
	for(int i = 1;i <= n;i++){
		memset(vis, 0, sizeof(vis)); ans = 0;
		for(int j = m;j >= 1;j--){
			dfs(i, j, 4);
			res[i][j] = std::min(res[i][j], ans);
		}
		for(int j = 1;j <= m;j++)
			printf("%d%c", res[i][j] > n * m * 2 ? -1 : res[i][j], j == m ? 10 : ' ');
	}
}
int main(){
	freopen("sandwich.in", "r", stdin);
	//freopen("sandwich.out", "w", stdout);
	for(int i = $(); i; i--) init();
	return 0;
}