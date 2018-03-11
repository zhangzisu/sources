#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200010
int n = $(), dfs[MAXN], bfs[MAXN], t[MAXN], v[MAXN];
int main(){
	for(int i = 1;i <= n;i++)t[dfs[i] = $()] = i;
	for(int i = 1;i <= n;i++)dfs[t[bfs[i] = $()]] = i, bfs[i] = i;
	for(int i = 1;i <= n;i++)t[dfs[i]] = i;
	register double ans = 2;
	register int l = 3, r = n;
	v[1] = v[2] = 1;
	for(int i = 3;i <= n;i++){
		if(t[i - 1] > t[i]){
			ans += 1;
		}else if(t[i - 1] + 1 == t[i] && l + n - r == i){
			ans += 0.5;
		}
		v[t[i]] = 1;
		while(l < r && v[l])l++;
		while(l < r && v[r])r--;
	}
	printf("%.3f\n", ans);
	return 0;
}
