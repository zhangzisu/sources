#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 5000
#define MAXM 5000000
int head[MAXN], next[MAXM], to[MAXM], tot, n, m;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
inline void $(int x1, int t1, int x2, int t2){
	if(t1 && t2){
		$(x1 << 1, x2 << 1 | 1);
		$(x2 << 1, x1 << 1 | 1);
	}else if(!t1 && t2){
		$(x1 << 1 | 1, x2 << 1 | 1);
		$(x2 << 1, x1 << 1);
	}else if(t1 && !t2){
		$(x1 << 1, x2 << 1);
		$(x2 << 1 | 1, x1 << 1 | 1);
	}else if(!t1 && !t2){
		$(x1 << 1 | 1, x2 << 1);
		$(x2 << 1 | 1, x1 << 1);
	}
}
int dfn[MAXN], low[MAXN], ins[MAXN], stk[MAXN], bel[MAXN], scc, tim, top;
void Tarjin(int x){
	dfn[x] = low[x] = ++tim;ins[stk[++top] = x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(dfn[to[i]]){
			if(ins[to[i]])low[x] = std::min(low[x], dfn[to[i]]);
		}else{
			Tarjin(to[i]);low[x] = std::min(low[x], low[to[i]]);
		}
	}
	if(low[x] == dfn[x]){
		scc++;
		do{
			bel[stk[top]] = scc;
			ins[stk[top]] = 0;
		}while(stk[top--] != x);
	}
}
inline bool _2_sat(){
	for(int i = 0;i < (n << 1);i++)if(!dfn[i])Tarjin(i);
	for(int i = 0;i < n;i++)if(bel[i << 1] == bel[i << 1 | 1])return 0;
	return 1;
}
int main(){
	while(~scanf("%d%d", &n, &m)){
		tot = scc = tim = top = 0;
		memset(head, -1, sizeof(head));
		memset(dfn, 0, sizeof(dfn));
		while(m--){
			int $1, $2, $3, $4;
			scanf("%d%d%d%d", &$1, &$2, &$3, &$4);
			$($1 ,$3, $2, $4);
		}
		puts(_2_sat() ? "YES" : "NO");
	}
	return 0;
}
