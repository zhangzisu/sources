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
#define MAXN 50000
int head[MAXN], to[MAXN], from[MAXN], next[MAXN], val[MAXN], cap[MAXN], tot = 0;
inline void $(int u, int v, int w, int c){
	next[tot] = head[u];to[tot] = v;from[tot] = u;val[tot] = w;cap[tot] = c;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;from[tot] = v;val[tot] =-w;cap[tot] = 0;head[v] = tot++;
}
#include<queue>
#define INF 0x3F3F3F3F
std::queue<int> Q;
int inq[MAXN], pre[MAXN], dis[MAXN], flo[MAXN], s, t, n = $(), m = $();
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
int main(){
	memset(head, -1, sizeof(head));
	while(m--){
		int $1 = $(), $2 = $(), $3 = $();
		$($1, $2, $3, 1);
		$($2, $1, $3, 1);
	}
	$(s = 0, 1, 0, 2);$(n, t = n + 1, 0, 2);
	printf("%d\n", mincost());
	return 0;
}
