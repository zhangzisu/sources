#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<queue>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 3010
#define MAXM 70010
#define INF 0x3F3F3F3F
int n = $(), m = $();
int head[MAXN], to[MAXM], next[MAXM], val[MAXM], tot = 0;
inline void $(int u, int v, int w){
	next[tot] = head[u];to[tot] = v;val[tot] = w;head[u] = tot++;
}
int HEAD[MAXN], TO[MAXM], NEXT[MAXM], D[MAXN], TOT = 0;
inline void $(int u, int v){
	NEXT[TOT] = HEAD[u];TO[TOT] = v;HEAD[u] = TOT++;
}
int d1[MAXN], d2[MAXN], vis[MAXN];
struct node{
	int x, dis;
	inline node(int x = 0, int dis = 0):x(x), dis(dis){}
	inline friend bool operator < (const node &a, const node &b){
		return a.dis > b.dis;
	}
};
std::priority_queue<node> Q;
inline int $(int s){
	memset(d1, 0x3F, sizeof(d1));
	memset(d2, 0, sizeof(d2));
	Q.push(node(s, d1[s] = d2[s] = 0));
	while(!Q.empty()){
		int top = Q.top().x, dis = std::max(d1[top], d2[top]);Q.pop();
		if(vis[top])continue;vis[top] = 1;
		for(int i = head[top];~i;i = next[i]){
			if(d1[to[i]] > dis + val[i]){
				d1[to[i]] = dis + val[i];
				if(!D[to[i]])Q.push(node(to[i], std::max(d1[to[i]], d2[to[i]])));
			}
		}
		for(int i = HEAD[top];~i;i = NEXT[i]){
			d2[TO[i]] = std::max(d2[TO[i]], dis);
			if(!--D[TO[i]])Q.push(node(TO[i], std::max(d1[TO[i]], d2[TO[i]])));
		}
	}
	return std::max(d1[n], d2[n]);
}
int main(){
	memset(head, -1, sizeof(head));
	memset(HEAD, -1, sizeof(HEAD));
	for(int i = 0;i < m;i++){
		int $1 = $(), $2 = $();
		$($1, $2, $());
	}
	for(int i = 1;i <= n;i++){
		for(int j = (D[i] = $());j;j--){
			$($(), i);
		}
	}
	printf("%d\n", $(1));
	return 0;
}
