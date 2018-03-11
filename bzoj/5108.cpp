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
#include<queue>
#include<map>
#include<bitset>
#define MAXN 50010
int n = $(), m = $(), s = $(), t = $();
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot;
inline void $(int u, int v, int w){
	next[tot] = head[u];to[tot] = v;val[tot] = w;head[u] = tot++;
}
struct E{
	int head[MAXN], D[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot;
	inline E(){
		memset(head, -1, sizeof(head));tot = 0;
	}
	inline void $(int u, int v, int w){
		next[tot] = head[u];to[tot] = v;val[tot] = w;head[u] = tot++;
		D[v]++;
	}
}B, C;
long long f1[MAXN], f2[MAXN], f[MAXN], d1[MAXN], d2[MAXN];
struct pair{
	long long first;int second;
	inline pair(long long f, int s):first(f), second(s){}
	inline bool friend operator < (const pair &a, const pair &b){return a.first > b.first;}
};
std::priority_queue<pair> Q;
inline void dj(int s, long long *dis){
	memset(dis, 0x3F, sizeof(long long) * n + 32);
	dis[s] = 0;Q.push(pair(0, s));
	register int cnt = 0;
	while(Q.size()){
		int x = Q.top().second;Q.pop();
		for(register int i = head[x];~i;i = next[i])
			if(dis[to[i]] > dis[x] + val[i])Q.push(pair(dis[to[i]] = dis[x] + val[i], to[i]));
	}
}
std::queue<int> sq;
std::bitset<MAXN> up[MAXN];
std::bitset<MAXN> down[MAXN];
std::map<long long, std::bitset<MAXN> > M;
long long ans = 0;
int main(){
	memset(head, -1, sizeof(head));
	while(m--){
		int $1 = $(), $2 = $(), $3 = $();
		$($1, $2, $3);
		$($2, $1, $3);
	}
	dj(s, d1);dj(t, d2);
	Q.push(pair(0, s));
	while(Q.size()){
		int x = Q.top().second;Q.pop();
		for(register int i = head[x];~i;i = next[i]){
			if(d1[to[i]] + d2[to[i]] != d1[t])continue;
			if(d1[to[i]] != d1[x] + val[i])continue;
			B.$(x, to[i], val[i]);C.$(to[i], x, val[i]);
			Q.push(pair(d1[to[i]], to[i]));
		}
	}
	for(register int i = 1;i <= n;i++)down[i].set(i);
	sq.push(s), f1[s] = 1;
	while(sq.size()){
		int x = sq.front();sq.pop();
		for(register int i = B.head[x];~i;i = B.next[i]){
			f1[B.to[i]] += f1[x];down[B.to[i]] |= down[x];if(!--B.D[B.to[i]])sq.push(B.to[i]);
		}
	}
	for(register int i = 1;i <= n;i++)up[i].set(i);
	sq.push(t), f2[t] = 1;
	while(sq.size()){
		int x = sq.front();sq.pop();
		for(register int i = C.head[x];~i;i = C.next[i]){
			f2[C.to[i]] += f2[x];up[C.to[i]] |= up[x];if(!--C.D[C.to[i]])sq.push(C.to[i]);
		}
	}
	for(register int i = 1;i <= n;i++)f[i] = f1[i] * f2[i];
	for(register int i = 1;i <= n;i++)M[f[i]].set(i);
	for(register int i = 1;i <= n;i++){
		long long rest = f[s] - f[i];
		if(!M.count(rest))continue;
		ans += (M[rest] & ~up[i] & ~down[i]).count();
	}
	printf("%lld\n", ans >> 1);
	return 0;
}
