#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 17
int n, m, map[MAXN][MAXN];
std::vector<int> next[MAXN], vtx;
long long f[MAXN][MAXN], ans;
void dp(int x, int fa){
	std::vector<int>::iterator it;
	for(it = next[x].begin();it != next[x].end();it++)if(*it != fa)dp(*it, x);
	for(int i = vtx.size() - 1;~i;i--){
		f[x][i] = 1;
		for(it = next[x].begin();it != next[x].end();it++)if(*it != fa){
			long long sum = 0;
			for(int j = vtx.size() - 1;~j;j--){
				if(map[vtx[i]][vtx[j]])sum += f[*it][j];
			}
			f[x][i] *= sum;
		}
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++){
		int u, v; scanf("%d%d", &u, &v);
		u--; v--;
		map[u][v] = map[v][u] = 1;
	}
	for(int i = 1;i < n;i++){
		int u, v; scanf("%d%d", &u, &v);
		u--; v--;
		next[u].push_back(v);
		next[v].push_back(u);
	}
	for(int d = 1;d < (1 << n);d++){
		vtx.clear();
		for(int i = 0;i < n;i++)if((d >> i) & 1)vtx.push_back(i);
		dp(0, -1);long long now = 0;
		for(int i = vtx.size() - 1;~i;i--)now += f[0][i];
		ans += ((__builtin_popcount(d) & 1) == (n & 1) ? 1 : -1) * now;
		//printf("%d\n", ans);
	}
	printf("%lld\n", ans);
	return 0;
}