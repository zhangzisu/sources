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
	int l, r, max[3], min[3], val[3], dat[3];
	inline node(int a = 0, int b = 0, int c = 0, int d = 0){
		l = r = 0;
		max[0] = min[0] = val[0] = a;
		max[1] = min[1] = val[1] = b;
		max[2] = min[2] = val[2] = c;
		dat[0] = dat[1] = dat[2] = d;
	}
	inline void print(){
		printf("Pos:{%3d%3d%3d}, Left:{%3d%3d%3d}, Right:{%3d,%3d,%3d}",
		min[0],max[0],val[0],
		min[1],max[1],val[1],
		min[2],max[2],val[2]
		);
	}
}p[MAXN << 1];
inline void pushUp(node &a, node &b){
	for(int i = 0;i < 3;i++){
		a.max[i] = std::max(a.max[i], b.max[i]);
		a.min[i] = std::min(a.min[i], b.min[i]);
	}
	a.dat[1] = std::min(a.dat[1], b.dat[1]);
	a.dat[2] = std::max(a.dat[2], b.dat[2]);
}
int D;
inline int cmp(const int &a, const int &b){
	return p[a].val[D] < p[b].val[D];
}
void Build(int &n, int l, int r, int d){
	int mid = (l + r) >> 1;D = d;
	std::nth_element(f + l, f + mid, f + r + 1, cmp);n = f[mid];
	if(l < mid)Build(p[n].l, l, mid - 1, (d + 1) % 3), pushUp(p[n], p[p[n].l]);
	if(r > mid)Build(p[n].r, mid + 1, r, (d + 1) % 3), pushUp(p[n], p[p[n].r]);
}
int ans, l, r, x, y;
void Query(int n){
	if(!n)return;
	if(p[n].max[0] < l || p[n].min[0] > r)return;
	if(p[n].dat[2] < ans || p[n].min[1] >= l || p[n].max[2] <= r)return;
	if(p[n].val[0] >= l && p[n].val[0] <= r &&
		p[n].val[1] < l && p[n].val[2] > r)ans = std::max(ans, p[n].dat[0]);
	Query(p[n].l);Query(p[n].r);
}
void print(int n = root, int deep = 0){
	if(!n){while(deep--)putchar(' ');puts("NULL");return;}
	print(p[n].l, deep + 4);
	for(int i=0;i<deep;i++)putchar(' ');p[n].print();putchar(10);
	print(p[n].r, deep + 4);
}
int main(){
	for(int i = 1;i <= n;i++){
		a[i] = $();
		pre[i] = tmp[a[i]];
		next[tmp[a[i]]] = i;
		tmp[a[i]] = i;
	}
	for(int i = 1;i <= n;i++)next[tmp[a[i]]] = n + 1;
	for(int i = 1;i <= n;i++)p[i] = node(i, pre[i], next[i], a[i]), f[i] = i;
	Build(root, 1, n, 0);
	//print();
	while(m--){
		x = $(), y = $();
		l = std::min((x + ans) % n + 1, (y + ans) % n + 1);
		r = std::max((x + ans) % n + 1, (y + ans) % n + 1);
		ans = 0;Query(root);
		printf("%d\n", ans);
	}
	return 0;
}
