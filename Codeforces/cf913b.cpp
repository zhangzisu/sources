#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 1010
int n, leaf[MAXN];
std::vector<int> next[MAXN];
int dfs(int x){
	if(next[x].empty())return leaf[x] = 1;
	register int cnt = 0;
	for(auto s : next[x]){
		if(!dfs(s))return 0;
		cnt += leaf[s];
	}
	return cnt >= 3;
}
int main(){
	scanf("%d", &n);
	for(int x, i = 2;i <= n;i++){
		scanf("%d", &x);
		next[x].push_back(i);
	}
	puts(dfs(1) ? "Yes" : "No");
	return 0;
}