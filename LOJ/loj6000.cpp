#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 1000
int head[MAXN], to[MAXN], next[MAXN], cap[MAXN], tot = 0;
inline void $(int u, int v, int c){
	next[tot] = head[u];to[tot] = v;cap[tot] = c;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;cap[tot] = 0;head[v] = tot++;
}
#include<queue>
#define INF 0x3F3F3F3F
int level[MAXN], s, t, n, m;
std::queue<int> Q;
inline int bfs(){
	memset(level, 0, sizeof(level));level[s] = 1;Q.push(s);
	while(Q.size()){
		int x = Q.front();Q.pop();
		for(int i = head[x];~i;i = next[i]){
			if(cap[i] && !level[to[i]]){
				level[to[i]] = level[x] + 1;
				Q.push(to[i]);
			}
		}
	}
	return level[t];
}
int dfs(int x, int flow){
	if(x == t || !flow)return flow;
	int ret = 0, f;
	for(int i = head[x];~i;i = next[i]){
		if((level[to[i]] == level[x] + 1) && cap[i] && (f = dfs(to[i], std::min(flow, cap[i])))){
			ret += f;flow -= f;cap[i] -= f;cap[i ^ 1] += f;
			if(!flow)return ret;
		}
	}
	return ret;
}
inline int dinic(){
	register int ret = 0;
	while(bfs())ret += dfs(s, INF);
	return ret;
}
int main(){
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	while(~scanf("%d%d", &s, &t))$(s, t, 1);
	for(int i = 1;i <= m;i++)$(0, i, 1);
	for(int i = n;i != m;i--)$(i, n + 1, 1);
	s = 0;t = n + 1;
	printf("%d\n", dinic());
	return 0;
}
