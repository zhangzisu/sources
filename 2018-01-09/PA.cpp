#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 10010
#define MAXM 200100
int head[MAXN], to[MAXM], from[MAXM], next[MAXM], val[MAXM], cap[MAXM], tot = 0;
inline void $(int u, int v, int w, int c){
	next[tot] = head[u];to[tot] = v;from[tot] = u;val[tot] = w;cap[tot] = c;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;from[tot] = v;val[tot] =-w;cap[tot] = 0;head[v] = tot++;
	printf("$ : %d => %d\n", u, v);
}
#include<queue>
#define INF 0x3F3F3F3F
std::queue<int> Q;
int inq[MAXN], pre[MAXN], dis[MAXN], flo[MAXN], s, t, n, m, k;
int spfa(int &flow, int &ans){
	memset(dis, 0x3F, sizeof(dis));memset(inq, 0, sizeof(inq));
	flo[s] = INF;dis[s] = 0;inq[s] = 1;Q.push(s);
	while(Q.size()){
		int x = Q.front();Q.pop();
		inq[x] = 0;
		for(int i = head[x];~i;i = next[i]){
			if(cap[i] && dis[to[i]] > dis[x] + val[i]){
				dis[to[i]] = dis[x] + val[i];
				pre[to[i]] = i;
				flo[to[i]] = std::min(flo[x], cap[i]);
				if(!inq[to[i]])Q.push(to[i]), inq[to[i]] = 1;
			}
		}
	}
	if(dis[t] == INF)return 0;
	flow = flo[t];ans = flow * dis[t];
	int x = t;
	while(x != s){
		cap[pre[x]] -= flow;cap[pre[x] ^ 1] += flow;
		x = from[pre[x]];
	}
	return 1;
}
inline int mincost(){
	register int ret = 0, tmp1 = 0, tmp2 = 0;
	while(spfa(tmp1, tmp2))ret += tmp2;
	return ret;
}
int ddd[105][105], d[20][2];
inline int P2P(int x, int y){return (x - 1) * m + y;}
inline bool judge(int x, int y){return x >= 1 && x <= n && y >= 1 && y <= m;}
int main(){
	int _;scanf("%d", &_);
	while(_--){
		scanf("%d%d%d", &n, &m, &k);
		memset(head, -1, sizeof(head));
		s = n * m + n * m + 2;
		t = tot = 0;
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++)
				scanf("%1d", &ddd[i][j]);
		for(int i = 1;i <= k;i++)scanf("%d%d", &d[i][0], &d[i][1]);
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				int now = P2P(i, j) + m * n;
				$(P2P(i, j), t, -ddd[i][j], 1);
				for(int x = 1;x <= k;x++){
					if(judge(i + d[x][0], j + d[x][1])){
						int to = P2P(i + d[x][0], j + d[x][1]);
						$(now, to, 0, 1);
					}
				}
				$(s - 1, now, 0, 1);
			}
		}
		$(s, s - 1, 0, 2);
		printf("%d\n", -mincost());
	}
	return 0;
}
