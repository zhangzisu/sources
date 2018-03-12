#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 10010
#define MAXM 40040
int n = $(), k = $(), m = $() - 1;
struct edge{
	int u, v, w1, w2;
}e[MAXM];
int p[MAXN], val[MAXM];
inline int find(int x){return x == p[x] ? x : p[x] = find(p[x]);}
inline int Judge(int lmt){
	for(int i = 1;i <= n;i++)p[i] = i;
	register int x = 1;
	for(int i = 1;i <= m && x < n;i++){
		if(e[i].w1 <= lmt){
			int U = find(e[i].u), V = find(e[i].v);
			if(U == V)continue;
			p[U] = V;x++;
		}
	}
	if(x <= k)return 0;
	for(int i = 1;i <= m && x < n;i++){
		if(e[i].w2 <= lmt){
			int U = find(e[i].u), V = find(e[i].v);
			if(U == V)continue;
			p[U] = V;x++;
		}
	}
	return x == n;
}
int main(){
	for(int i = 1;i <= m;i++){
		e[i].u = $();e[i].v = $();e[i].w1 = $();e[i].w2 = $();
	}
	register int l = 1, r = 30000, mid, ans = 0;
	while(l <= r){
		mid = (l + r) >> 1;
		if(Judge(mid))ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
