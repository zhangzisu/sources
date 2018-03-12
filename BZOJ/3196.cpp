#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
//inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline char gc(){return getchar();}
inline int $(){
	register int x = 0, f = 0;register char ch = gc(); 
	while(!isdigit(ch) && (ch ^ 45))ch = gc();
	if(!(ch ^ 45))ch = getchar(), f = 1;
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<set>
#define MAXN 50010
struct splay{
	splay *l, *r, *f;int val, size;
	inline splay(int val = 0, int size = 1):val(val), size(size){l = r = f = NULL;}
};
inline void print(splay *root, int deep = 0){
	if(!root){
		printf("DEBUG |");
		for(int i = 1;i <= deep;i++)putchar(' ');
		puts("NULL");
		return;
	}
	print(root->r, deep + 4);
	printf("DEBUG |");
	for(int i = 1;i <= deep;i++)putchar(' ');
	printf("Splay node 0X%010X, val %3d, size %3d\n", (int*)root, root->val, root->size);
	print(root->l, deep + 4);
}
inline void pushUp(splay *x){x->size = 1 + (x->l ? x->l->size : 0) + (x->r ? x->r->size : 0);}
inline void rr(splay *x){
	splay *f = x->f;f->l = x->r;if(f->l)f->l->f = f;
	if(f->f){if(f->f->l == f)f->f->l = x;else f->f->r = x;}
	x->f = f->f;f->f = x;x->r = f;pushUp(f);pushUp(x);
}
inline void lr(splay *x){
	splay *f = x->f;f->r = x->l;if(f->r)f->r->f = f;
	if(f->f){if(f->f->l == f)f->f->l = x;else f->f->r = x;}
	x->f = f->f;f->f = x;x->l = f;pushUp(f);pushUp(x);
}
inline void Splay(splay *x){
	while(x->f){
		if(x->f->f){if(x->f->f->l == x->f)rr(x->f);else lr(x->f);}
		if(x->f->l == x)rr(x);else lr(x);
	}
}
inline void del(splay *org){if(org)del(org->l), del(org->r), delete org;}
inline splay* insert(splay *root, int val){
	if(!root)return new splay(val);
	register splay *p = root, *f = NULL;
	while(p){f = p;if(val <= p->val)p = p->l;else p = p->r;}
	if(val <= f->val)(f->l = new splay(val))->f = f;
	else (f->r = new splay(val))->f = f;
	while(f){pushUp(f);f = f->f;}
	return root;
}
splay *Q[MAXN];
inline splay* Merge(splay *l, splay *r){
	Splay(l);Splay(r);
	if(l->size > r->size){splay *t = l;l = r;r = t;}
	splay *ret = r;register int H, T;Q[H = T = 0] = l;
	while(H <= T){ret = insert(ret, Q[H]->val);if(Q[H]->l)Q[++T] = Q[H]->l;if(Q[H]->r)Q[++T] = Q[H]->r;++H;}
	del(l);Splay(ret);return ret;
}
inline splay* remove(splay *root, int val){
	if(root)Splay(root);splay *p = root;
	while(p){if(p->val == val)break;else if(p->val < val)p = p->r;else p = p->l;}
	if(!p)return root;Splay(p);
	if(!p->l && !p->r){del(p);return NULL;}
	if(p->l){p->l->f = NULL;if(!p->r)return p->l;}
	if(p->r){p->r->f = NULL;if(!p->l)return p->r;}
	root = Merge(p->l, p->r);p->l = p->r = NULL;del(p);
	return root;
}
splay *val[MAXN << 2];
int n = $(), m = $(), a[MAXN];
void Insert(int n, int l, int r, int p){
	val[n] = insert(val[n], a[p]);
	if(l == r)return;
	int mid = (l + r) >> 1;
	if(p <= mid)Insert(n << 1, l, mid, p);else Insert(n << 1 | 1, mid + 1, r, p);
}
void Modify(int n, int l, int r, int p, int v){
	val[n] = remove(val[n], a[p]);val[n] = insert(val[n], v);
	if(l == r)return;
	int mid = (l + r) >> 1;
	if(p <= mid)Modify(n << 1, l, mid, p, v);else Modify(n << 1 | 1, mid + 1, r, p, v);
}
inline int size(splay *x){return x ? x->size : 0;}
inline int findRank(splay *root, int val){
	Splay(root);
	int ret = 0;
	while(root){
		if(root->val == val)return ret + size(root->l);
		else if(root->val < val)ret += size(root->l) + 1, root = root->r;
		else root = root->l;
	}
	return ret;
}
int FindRank(int n, int l, int r, int L, int R, int x){
	if(l == L && r == R)return findRank(val[n], x);
	int mid = (l + r) >> 1;
	if(R <= mid)return FindRank(n << 1, l, mid, L, R, x);
	else if(L > mid)return FindRank(n << 1 | 1, mid + 1, r, L, R, x);
	else return FindRank(n << 1, l, mid, L, mid, x) + FindRank(n << 1 | 1, mid + 1, r, mid + 1, R, x);
}
inline int preRank(splay *root, int val){
	Splay(root);
	register int ret = -0x7FFFFFFF;
	while(root){
		if(root->val < val)ret = std::max(ret, root->val), root = root->r;
		else root = root->l;
	}
	return ret;
}
int PreRank(int n, int l, int r, int L, int R, int x){
	if(l == L && r == R)return preRank(val[n], x);
	int mid = (l + r) >> 1;
	if(R <= mid)return PreRank(n << 1, l, mid, L, R, x);
	else if(L > mid)return PreRank(n << 1 | 1, mid + 1, r, mid + 1, R, x);
	else return std::max(PreRank(n << 1, l, mid, L, mid, x) ,PreRank(n << 1 | 1, mid + 1, r, mid + 1, R, x));
}
inline int nextRank(splay *root, int val){
	Splay(root);
	register int ret = 0x7FFFFFFF;
	while(root){
		if(root->val > val)ret = std::min(ret, root->val), root = root->l;
		else root = root->r;
	}
	return ret;
}
int NextRank(int n, int l, int r, int L, int R, int x){
	if(l == L && r == R)return nextRank(val[n], x);
	int mid = (l + r) >> 1;
	if(R <= mid)return NextRank(n << 1, l, mid, L, R, x);
	else if(L > mid)return NextRank(n << 1 | 1, mid + 1, r, L, R, x);
	return std::min(NextRank(n << 1, l, mid, L, mid, x), NextRank(n << 1 | 1, mid + 1, r, mid + 1, R, x));
}
int ccf = 0;
int main(){
	for(int i = 1;i <= n;i++)a[i] = $(), ccf = std::max(ccf, a[i]), Insert(1, 1, n, i);
	while(m--){
		int pos, k, l, r;
		register int L, R, ans;
		switch($()){
			case 1:
				l = $(), r = $(), k = $();
				printf("%d\n", FindRank(1, 1, n, l, r, k) + 1);
				break;
			case 2:
				l = $(), r = $(), k = $();
				L = 0;R = ccf + 1;ans = 0;
				while(L <= R){
					int mid = (L + R) >> 1;
					if(FindRank(1, 1, n, l, r, mid) < k)ans = mid, L = mid + 1;
					else R = mid - 1;
				}
				printf("%d\n", ans);
				break;
			case 3:
				pos = $(), k = $();
				Modify(1, 1, n, pos, k);a[pos] = k;
				ccf = std::max(ccf, k);
				break;
			case 4:
				l = $(), r = $(), k = $();
				printf("%d\n", PreRank(1, 1, n, l, r, k));
				break;
			case 5:
				l = $(), r = $(), k = $();
				printf("%d\n", NextRank(1, 1, n, l, r, k));
				break;
		}
	}
	return 0;
}
