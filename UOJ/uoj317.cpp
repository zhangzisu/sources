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
inline char ga(){
	register char ch = gc();
	while(!isalpha(ch))ch = gc();
	return ch;
}
#define MAXN 100010
#define MAXM 200010
int a[MAXN], b[MAXN], n = $(), m = 0, d = $(), q;
int a1[MAXM], a2[MAXM], b1[MAXM], b2[MAXM];
int head[MAXN], to[MAXM], next[MAXM], tot;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
int dfn[MAXN], low[MAXN], ins[MAXN], stk[MAXN], bel[MAXN], scc, top, tim;
inline int GetPos(int x, int y){
	if(a[x] == 0)return (x << 1) + (y - 1);
	if(a[x] == 1)return (x << 1) + (y ? 1 : 0);
	return (x << 1) + y;
}
inline int GetVal(int x, int y){
	if(a[x] == 0)return y + 1;
	if(a[x] == 1)return y ? 2 : 0;
	return y;
}
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
		++scc;
		do{
			ins[stk[top]] = 0;
			bel[stk[top]] = scc;
		}while(stk[top--] != x);
	}
}
inline bool _2_sat(){
	scc = top = tim = tot = 0;
	memset(head, -1, sizeof(head));
	memset(dfn, 0, sizeof(dfn));
	for(register int i = 1;i <= q;i++){
		const int A = GetPos(a1[i], a2[i]), B = GetPos(b1[i], b2[i]);
		if(a[a1[i]] == a2[i]){
			continue;
		}else if(a[b1[i]] == b2[i]){
			$(A, A ^ 1);
		}else{
			$(A, B);$(B ^ 1, A ^ 1);
		}
	}
	for(register int i = 2;i <= (n << 1) + 1;i++)if(!dfn[i])Tarjin(i);
	for(register int i = 1;i <= n;i++)if(bel[i << 1] == bel[i << 1 | 1])return 0;
	for(register int i = 1;i <= n;i++){
		if(bel[i << 1] < bel[i << 1 | 1])putchar(GetVal(i, 0) + 'A');
		else putchar(GetVal(i, 1) + 'A');
	}
	return 1;
}
int main(){
	for(register int i = 1;i <= n;i++){
		int now = ga() - 'a';
		if(now < 3)a[i] = now;
		else b[m++] = i;
	}
	q = $();
	for(register int i = 1;i <= q;i++){
		a1[i] = $();a2[i] = ga() - 'A';
		b1[i] = $();b2[i] = ga() - 'A';
	}
	for(register int i = 0;i < (1 << m);i++){
		for(register int j = 0;j < m;j++){
			if((i >> j) & 1)a[b[j]] = 0;
			else a[b[j]] = 1;
		}
		if(_2_sat())return 0;
	}
	puts("-1");
	return 0;
}
