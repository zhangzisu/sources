#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
//inline char gc(){return getchar();}
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline int c(){
	register char ch = gc();
	while(!isalpha(ch))ch = gc();
	return ch;
}
#define MAXN 1000010
#define alpha 0.75
#define INF 0x7FFFFFFFFFFFFFFFLL
long long V[MAXN], VL[MAXN], VR[MAXN];
struct data{
	int l, r;
	inline bool friend operator < (const data &a, const data &b){
		return V[a.l] < V[b.l] || (V[a.l] == V[b.l] && V[a.r] < V[b.r]);
	}
	inline bool friend operator == (const data &a, const data &b){
		return a.l == b.l && a.r == b.r;
	}
	inline bool friend operator <= (const data &a, const data &b){return a < b || a == b;}
};
struct SGT{
	struct node{
		int l, r, f, s;data v;
	}p[MAXN];
	int q[MAXN], top, cnt, root, goat;
	inline SGT(){cnt = root = 0;}
	void dfs(int x){if(p[x].l)dfs(p[x].l);q[++top] = x;if(p[x].r)dfs(p[x].r);}
	int build(int l, int r, long long L, long long R){
		int x = q[(l + r) >> 1], mid = (l + r) >> 1;long long MID = (L >> 1) + (R >> 1);
		V[x] = MID;VL[x] = L;VR[x] = R;p[x].l = p[x].r = p[x].f = 0;
		if(l < mid)p[p[x].l = build(l, mid - 1, L, MID)].f = x;
		if(r > mid)p[p[x].r = build(mid + 1, r, MID, R)].f = x;
		p[x].s = p[p[x].l].s + p[p[x].r].s + 1;
		return x;
	}
	inline void rebuild(int n){
		int f = p[n].f;top = 0;dfs(n);
		if(!f){root = build(1, top, VL[n], VR[n]);return;}
		if(n == p[f].l)p[p[f].l = build(1, top, VL[n], VR[n])].f = f;
		else p[p[f].r = build(1, top, VL[n], VR[n])].f = f;
		p[f].s = p[p[f].l].s + p[p[f].r].s;
	}
	int insert(int n, data val, long long L, long long R, int &pos){
		if(!n){
			pos = ++cnt;
			p[cnt].v = val;p[cnt].l = p[cnt].r = 0;
			p[cnt].s = 1;V[cnt] = (L >> 1) + (R >> 1);VL[cnt] = L;VR[cnt] = R;
			return cnt;
		}
		if(p[n].v == val)return pos = n;
		if(val < p[n].v)p[p[n].l = insert(p[n].l, val, VL[n], V[n], pos)].f = n;
		else p[p[n].r = insert(p[n].r, val, V[n], VR[n], pos)].f = n;
		p[n].s = p[p[n].l].s + p[p[n].r].s;
		if(p[n].s * alpha < std::max(p[p[n].l].s, p[p[n].r].s))goat = n;
		return n;
	}
	void print(int n, int deep = 0){
		if(!n){
			for(int i=0;i<deep;i++)putchar(' ');
			puts("NULL");
			return;
		}
		print(p[n].r,deep+4);
		for(int i=0;i<deep;i++)putchar(' ');
		printf("%d data:{%d, %d}, V=%lld\n", n,p[n].v.l,p[n].v.r,V[n]);
		print(p[n].l,deep+4);
	}
}sgt;
int n = $(), m = $(), min[MAXN], pos[MAXN];
inline int mmin(int x, int y){return V[pos[x]] > V[pos[y]] || (V[pos[x]] == V[pos[y]] && x < y)? x : y;}
void Modify(int n, int l, int r, int p){
	if(l == r){min[n] = p;return;}
	int mid = (l + r) >> 1;
	if(p <= mid)Modify(n << 1, l, mid, p);else Modify(n << 1 | 1, mid + 1, r, p);
	min[n] = mmin(min[n << 1], min[n << 1 | 1]);
}
int Query(int n, int l, int r, int L, int R){
	if(l == L && r == R)return min[n];
	int mid = (l + r) >> 1;
	if(R <= mid)return Query(n << 1, l, mid, L, R);
	else if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R);
	else return mmin(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
int main(){
	V[0] = VL[0] = VR[0] = 0x8000000000000000LL;
	sgt.root = sgt.insert(sgt.root, (data){0, 0}, -INF, INF, sgt.root);
	for(int i = 1;i <= n;i++)pos[i] = sgt.root, Modify(1, 1, n, i);
	while(m--){
		if(c() == 'C'){
			int l = $(), r = $(), k = $();
			sgt.insert(sgt.root, (data){pos[l], pos[r]}, VL[sgt.root], VR[sgt.root], pos[k]);
			if(sgt.goat)sgt.rebuild(sgt.goat), sgt.goat = 0;
			Modify(1, 1, n, k);
			//sgt.print(sgt.root);
		}else{
			int l = $(), r = $();
			printf("%d\n", Query(1, 1, n, l, r));
		}
	}
	return 0;
}
