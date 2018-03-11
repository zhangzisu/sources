#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 1010
#define INF 0x3F3F3F3F
int head[MAXN], to[MAXN << 1], next[MAXN << 1], ret[MAXN << 1], tot = 0;
inline void $(int u, int v, int c){
	next[tot] = head[u];to[tot] = v;ret[tot] = c;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;ret[tot] = 0;head[v] = tot++;
}
#include<queue>
std::queue<int> Q;
int level[MAXN], n, m, s, t;
inline int BFS(){
	memset(level, 0, sizeof(level));level[s] = 1;
	Q.push(s);
	while(Q.size()){
		int x = Q.front();Q.pop();
		for(int i = head[x];~i;i = next[i]){
			if(!level[to[i]] && ret[i]){
				level[to[i]] = level[x] + 1;
				Q.push(to[i]);
			}
		}
	}
	return level[t];
}
int DFS(int x, int flow){
	if(x == t || !flow)return flow;
	int res = 0, f;
	for(int i = head[x];~i;i = next[i]){
		if((level[to[i]] == level[x] + 1) && ret[i]){
			f = DFS(to[i], std::min(flow, ret[i]));
			res += f;ret[i] -= f;ret[i ^ 1] += f;flow -= f;
			if(!flow)return res;
		}
	}
	return res;
}
inline int Dinic(){
	int ret = 0;
	while(BFS())ret += DFS(s, INF);
	return ret;
}
int main(){
	while(~scanf("%d%d", &m, &n)){
		s = 1;t = n;
		memset(head, -1, sizeof(head));tot = 0;
		while(m--){
			int $1, $2, $3;scanf("%d%d%d", &$1, &$2, &$3);
			$($1, $2, $3);
		}
		printf("%d\n", Dinic());
	}
}
