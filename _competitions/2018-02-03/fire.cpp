#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 200
int n, f[MAXN][5000], g[MAXN][5000], ans = -1;
std::vector<int> V;
struct ckr{
	int t, d, p, lim, pos;
	inline void read(int i){
		scanf("%d%d%d", &t, &d, &p);
		lim = d - t;pos = i;
	}
	inline friend bool operator < (const ckr &a, const ckr &b){
		return a.d < b.d;
	}
}zp[MAXN];
int id[MAXN];
int main(){
	freopen("fire.in", "r", stdin);
	freopen("fire.out", "w", stdout);

	scanf("%d", &n);
	for(int i = 1;i <= n;i++)zp[i].read(i);
	std::sort(zp + 1, zp + n + 1);
	for(int i = 1;i <= n;i++)id[i] = zp[i].pos;
	for(int i = 1;i <= n;i++){
		for(int j = 0;j < 5000;j++){
			if(zp[i].lim > j){
				if(f[i][j + zp[i].t] < f[i - 1][j] + zp[i].p){
					f[i][j + zp[i].t] = f[i - 1][j] + zp[i].p;
					g[i][j + zp[i].t] = j;
				}
			}
			if(f[i][j] < f[i - 1][j]){
				f[i][j] = f[i - 1][j];
				g[i][j] = j;
			}
		}
	}
	int pos;
	for(int i = 0;i < 5000;i++){
		if(ans < f[n][i]){
			ans = f[n][i];
			pos = i;
		}
	}
	for(int i = n;i;i--){
		int pre = g[i][pos];
		if(pre != pos)V.push_back(i);
		pos = pre;
	}
	printf("%d\n%u\n", ans, V.size());
	std::reverse(V.begin(), V.end());
	for(std::vector<int>::iterator it = V.begin();it != V.end();it++){
		printf("%d ", id[*it]);
	}
	puts("");
	return 0;
}