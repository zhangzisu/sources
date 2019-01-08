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
#define MAXN 100010
int n = $(), k = $(), D, f[MAXN], x, y, root;
struct node{
	int pos[2], x[2], y[2], l, r;
}p[MAXN << 2];
inline void pushUp(node &a, node &b){
	a.x[0] = std::min(a.x[0], b.x[0]);a.x[1] = std::max(a.x[1], b.x[1]);
	a.y[0] = std::min(a.y[0], b.y[0]);a.y[1] = std::max(a.y[1], b.y[1]);
}
inline long long _(int x){return (long long)x * x;}
std::priority_queue<long long, std::vector<long long>, std::greater<long long> > Q;
inline bool cmp(const int &a, const int &b){return p[a].pos[D] < p[b].pos[D];}
void Build(int &n, int l, int r, int d){
	D = d;int mid = (l + r) >> 1;
	std::nth_element(f + l, f + mid, f + r + 1, cmp);n = f[mid];
	if(l < mid)Build(p[n].l, l, mid - 1, !d), pushUp(p[n], p[p[n].l]);
	if(r > mid)Build(p[n].r, mid + 1, r, !d), pushUp(p[n], p[p[n].r]);
}
inline long long md(int n){
	return
		std::max(_(p[n].x[0] - x), _(p[n].x[1] - x)) +
		std::max(_(p[n].y[0] - y), _(p[n].y[1] - y));
}
inline long long dd(int n){
	return _(p[n].pos[0] - x) + _(p[n].pos[1] - y);
}
void Query(int n){
	long long ml = md(p[n].l), mr = md(p[n].r), dm = dd(n);
	if(dm > Q.top())Q.pop(), Q.push(dm);
	if(ml > mr){
		if(p[n].l && ml > Q.top())Query(p[n].l);
		if(p[n].r && mr > Q.top())Query(p[n].r);
	}else{
		if(p[n].r && mr > Q.top())Query(p[n].r);
		if(p[n].l && ml > Q.top())Query(p[n].l);
	}
}
int main(){
	for(int i = 1;i <= n;i++){
		p[i].pos[0] = p[i].x[0] = p[i].x[1] = $();
		p[i].pos[1] = p[i].y[0] = p[i].y[1] = $();
		f[i] = i;
	}
	Build(root, 1, n, 0);
	for(int i = 1;i <= (k << 1);i++)Q.push(0);
	for(int i = 1;i <= n;i++){
		x = p[i].pos[0];y = p[i].pos[1];
		Query(root);
	}
	printf("%lld\n", Q.top());
	return 0;
}
