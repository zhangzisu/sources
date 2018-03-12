#include<cstdio>
#include<cctype>
inline short $(){
	register short x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<algorithm>
#define MAXN 5010
short n = $(), r = $(), a[MAXN][MAXN], s[MAXN][MAXN], ans = 0;
inline short calc(int x, int y){
	return s[x][y] - s[x - r][y] - s[x][y - r] + s[x - r][y - r];
}
int main(){
	while(n--){
		a[$() + 1][$() + 1] = $();
	}
	for(int i = 1;i < MAXN;i++)
		for(int j = 1;j < MAXN;j++)
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
	for(int i = r;i < MAXN;i++)
		for(int j = r;j < MAXN;j++)
			ans = std::max(ans, calc(i, j));
	printf("%d\n", ans);
	return 0;
}
