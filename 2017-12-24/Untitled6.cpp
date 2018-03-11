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
#define MAXN 100010
int n = $(), m = $(), a[MAXN], pre[MAXN], next[MAXN], tmp[MAXN], f[MAXN], root;
struct node{
	int l, r, max[4], min[4], val[4], dat;
	inline node(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0){
		l = r = 0;dat = e;
		max[0] = min[0] = val[0] = a;
		max[1] = min[1] = val[1] = b;
		max[2] = min[2] = val[2] = c;
		max[3] = min[3] = val[3] = d;
	}
}p[MAXN << 1];
inline void pushUp(node &a, node &b){
	for(int i = 0;i < 4;i++){
		a.max[i] = std::max(a.max[i], b.max[i]);
		a.min[i] = std::min(a.min[i], b.min[i]);
	}
}
int D;
inline int cmp(const int &a, const int &b){
	return p[a].val[D] < p[b].val[D];
}
void Build(int &n, int l, int r, int d){
	int mid = (l + r) >> 1;D = d;
	std::nth_element(f + l, f + mid, f + r + 1, cmp);n = f[mid];
	if(l < mid)Build(p[n].l, l, mid - 1, (d + 1) % 4), pushUp(p[n], p[p[n].l]);
	if(r > mid)Build(p[n].r, mid + 1, r, (d + 1) % 4), pushUp(p[n], p[p[n].r]);
}
unsigned long long ans;
int u, d, l, r;
inline bool check(int n){
	if(p[n].min[0] > d || p[n].max[1] < u || p[n].min[2] > r || p[n].max[3] < l)return 0;
	return 1;
}
inline bool range(int x, int l, int r){
	return x >= l && x <= r;
}
inline bool ck(const int &n){
	if(p[n].val[0] <= d && p[n].val[1] >= u && p[n].val[2] <= r && p[n].val[3] >= l)return 1;
	return 0;
}
inline unsigned long long calc(int n){
	return (unsigned long long)
		(std::min(p[n].val[3], r) - std::max(p[n].val[2], l) + 1) *
		(std::min(p[n].val[1], d) - std::max(p[n].val[0], u) + 1) *
		p[n].dat;
}
void Query(int n){
	if(!n || !check(n))return;
	if(ck(n))ans += calc(n);
	Query(p[n].l);Query(p[n].r);
}
int W = $(), q = $();
int main(){
	for(int i = 1;i <= W;i++){
		int u = $(), d = $(), l = $(), r = $();
		p[i] = node(u, d, l, r, $());
		f[i] = i;
	}
	Build(root, 1, W, 0);
	while(q--){
		int x = $(), y = $();
		u = ans % n + 1;
		d = (ans + x) % n + 1;
		if(u > d)std::swap(u, d);
		l = ans % m + 1;
		r = (ans + y) % m + 1;
		if(l > r)std::swap(l, r);
		ans = 0;
		Query(root);
		printf("%llu\n", ans);
	}
	return 0;
}
