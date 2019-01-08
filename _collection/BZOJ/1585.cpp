#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100000
#define INF 0x3F3F3F3F
int head[MAXN], to[MAXN], next[MAXN], cap[MAXN], tot = 0;
inline void $(int u, int v, int c){
	next[tot] = head[u];to[tot] = v;cap[tot] = c;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;cap[tot] = 0;head[v] = tot++;
}
#include<queue>
std::queue<int> Q;
int level[MAXN], s, t, p = $(), c = $(), n = $(), sb[MAXN];
inline int bfs(){
	memset(level, 0, sizeof(level));
	Q.push(s);level[s] = 1;
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
			ret += f;cap[i] -= f;cap[i ^ 1] += f;flow -= f;
			if(!flow)return ret;
		}
	}
	return ret;
}
inline int dinic(){
	int ret = 0;
	while(bfs())ret += dfs(s, INF);
	return ret;
}
int main(){
	memset(head, -1, sizeof(head));
	while(c--){
		int $1 = $(), $2 = $();
		$($1 + p, $2, INF);
		$($2 + p, $1, INF);
	}
	while(n--){
		int $1 = $();
		$(0, $1, INF);
		sb[$1] = 1;
	}
	for(int i = 1;i <= p;i++)
		if(i == 1 || sb[i])$(i, i + p, INF);
		else $(i, i + p, 1);
	s = 0;t = 1 + p;
	printf("%d\n", dinic());
	return 0;
}
