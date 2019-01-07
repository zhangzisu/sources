#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 20010
#define MAXE 200010
#define MAXK 22
int n, m, k, q;
int head[MAXN], to[MAXE << 1], next[MAXE << 1], val[MAXE << 1], tot = 0;
inline void $(int u, int v, int w){
	next[tot] = head[u]; to[tot] = v; val[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; val[tot] = w; head[v] = tot++;
}
int dis[MAXK][MAXK], ban[MAXK], f[1 << 20][MAXK];
inline void dijkstra(int x){
	static int dis[MAXN];
	static std::priority_queue<std::pair<int, int> > Q;
	static bool vis[MAXN];
	memset(vis,    0, sizeof(vis));
	memset(dis, 0x3F, sizeof(int) * MAXN);
	dis[x] = 0; Q.push(std::make_pair(0, x));
	while(Q.size()){
		int t = Q.top().second; Q.pop();
		if(vis[t])continue;
		vis[t] = 1;
		for(int i = head[t];~i;i = next[i]){
			if(dis[to[i]] > dis[t] + val[i]){
				dis[to[i]] = dis[t] + val[i];
				Q.push(std::make_pair(-dis[to[i]], to[i]));
			}
		}
	}
	::dis[x][0] = dis[n];
	for(int i = 1;i <= k + 1;i++)::dis[x][i] = dis[i];
}
int main(){
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1, u, v, w;i <= m;i++){
		scanf("%d%d%d", &u, &v, &w);
		$(u, v, w);
	}
	for(int i = 1;i <= k + 1;i++)dijkstra(i);
	scanf("%d", &q);
	while(q--){
		int u, v; scanf("%d%d", &u, &v);
		ban[v] |= 1 << (u - 2);
	}
	memset(f, 0x3F, sizeof(f)); f[0][1] = 0;
	for(int d = 0;d < (1 << k);d++){
		for(int i = 1;i <= k + 1;i++){
			if(f[d][i] == 0x3F3F3F3F)continue;
			for(int j = 2;j <= k + 1;j++){
				if((d & ban[j]) != ban[j])continue;
				f[d | (1 << (j - 2))][j] =
					std::min(
						f[d | (1 << (j - 2))][j],
						f[d][i] + dis[i][j]
					);
			}
		}
	}
	int ans = (~0u) >> 1;
	for(int i = 1;i <= k + 1;i++)ans = std::min(ans, f[(1 << k) - 1][i] + dis[i][0]);
	printf("%d\n", ans);
	return 0;
}