#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<set>
#define MAXN 105
int t, n, m, k, ans, res;
int balabala[MAXN][MAXN], d[20][2];
std::set<std::pair<int, int > > ckr;
int main(){
	scanf("%d", &t);
	while(t--){
		res = 0;
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++)
				scanf("%1d", &balabala[i][j]);
		for(int i = 1;i <= k;i++)scanf("%d%d", &d[i][0], &d[i][1]);
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++)
				for(int k = 1;k <= n;k++)
					for(int l = 1;l <= m;l++){
						ckr.clear();ans = 0;
						for(int x = 1;x <= k;x++){
							ckr.insert(std::make_pair(i + d[x][0], j + d[x][1]));
							ckr.insert(std::make_pair(k + d[x][0], l + d[x][1]));
						}
						for(std::set<std::pair<int, int > >::iterator it = ckr.begin();
							it != ckr.end();it++)ans += balabala[(*it).first][(*it).second];
						res = std::max(res, ans);
					}
		printf("%d\n", res);
	}
	return 0;
}

