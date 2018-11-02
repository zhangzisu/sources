#include<algorithm>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
int n, m, vis[52];
inline int cvt(char ch){
	return islower(ch) ? ch - 'a' + 26 : ch - 'A';
}
int cnt[52], ans;
std::vector<int> cond[52];
void dfs(int x){
	if(x > n){
		for(int i=0;i<52;i++){
			if(!vis[i])continue;
			for(int j=0;j<(int)cond[i].size();j++){
				if(cnt[i]%cond[i][j]==0)goto succ;
			}
			return;
			succ:;
		}
		ans++;
		ans%=12345;
		return;
	}
	for(int i = 0;i < 52;i++){
		if(!vis[i])continue;
		cnt[i]++;
		dfs(x+1);
		cnt[i]--;
	}
}
char buf[50];
int main(){
	freopen("too.in", "r", stdin);
	freopen("too.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1, v;i <= m;i++){
		scanf("%s%d", buf, &v);
		cond[cvt(buf[0])].push_back(v);
		vis[cvt(buf[0])] = 1;
	}
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
