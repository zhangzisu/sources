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
#define INF 0x3F3F3F3F
struct splay{
	splay *l, *r, *f, *min;
	int val, size, tag;
	inline splay(int val = 0, int size = 1):val(val), size(size){l = r = f = NULL;min = this;tag = 0;}
}*root;
inline void Update(splay *x){
	x->size = 1;x->min = x;
	if(x->l){
		x->size += x->l->size;
		x->min = x->l->min->val < x->min->val ? x->l->min : x->min;
	}
	if(x->r){
		x->size += x->r->size;
		x->min = x->r->min->val < x->min->val ? x->r->min : x->min;
	}
}
inline void pushDown(splay *x){
	if(!x->tag)return;
	splay *t = x->l;x->l = x->r;x->r = t;
	if(x->l)x->l->tag ^= 1;if(x->r)x->r->tag ^= 1;
	x->tag = 0;
}
int n = $(), v[MAXN];
std::pair<int, int> a[MAXN];
inline splay* build(int l, int r){
	if(l == r)return new splay(v[l]);
	int mid = (l + r) >> 1;
	splay *now = new splay(v[mid]);
	if(l <= mid - 1)(now->l = build(l, mid - 1))->f = now;
	if(mid + 1 <= r)(now->r = build(mid + 1, r))->f = now;
	Update(now);
	return now;
}
inline void lr(splay *x, splay *f){
	f->r = x->l;
	if(f->r)f->r->f = f;
	if(f->f){
		if(f->f->l == f)f->f->l = x;
		if(f->f->r == f)f->f->r = x;
	}
	x->f = f->f;f->f = x;x->l = f;
	Update(f);Update(x);
}
inline void rr(splay *x, splay *f){
	f->l = x->r;
	if(f->l)f->l->f = f;
	if(f->f){
		if(f->f->l == f)f->f->l = x;
		if(f->f->r == f)f->f->r = x;
	}
	x->f = f->f;f->f = x;x->r = f;
	Update(f);Update(x);
}
inline void Splay(splay *x, splay *g){
	while(x->f != g){
		if(x->f->f == g){
			pushDown(x->f);pushDown(x);
			if(x->f->l == x)rr(x, x->f);
			else lr(x, x->f);
		}else{
			pushDown(x->f->f);pushDown(x->f);pushDown(x);
			if(x->f->f->l == x->f)
				if(x->f->l == x)rr(x->f, x->f->f), rr(x, x->f);
				else lr(x, x->f), rr(x, x->f);
			else
				if(x->f->r == x)lr(x->f, x->f->f), lr(x, x->f);
				else rr(x, x->f), lr(x, x->f);
		}
	}
	if(g == NULL)root = x;
}
inline int size(splay *x){return x ? x->size : 0;}
inline splay* Node(int pos){
	splay *p = root;
	while(p){
		pushDown(p);
		if(size(p->l) > pos)p = p->l;
		else if(size(p->l) == pos)return p;
		else if(size(p->l) < pos)pos -= size(p->l) + 1, p = p->r;
	}
	return p;
}
inline splay* r(int l, int r){
	Splay(Node(l - 1), NULL);Splay(Node(r + 1), root);
	return root->r->l;
}
inline void print(splay *root, int deep){
	for(int i = 1;i <= deep;i++)putchar(' ');printf("val:%d size:%d\n", root->val, root->size);
	if(root->l)print(root->l, deep + 2);
	if(root->r)print(root->r, deep + 2);
}
int main(){
	for(int i = 1;i <= n;i++)a[i] = std::make_pair($(), i);
	std::sort(a + 1, a + n + 1);
	for(int i = 1;i <= n;i++)v[a[i].second] = i;
	root = new splay(-INF, 2);
	(root->r = new splay(INF))->f = root;
	(root->r->l = build(1, n))->f = root->r;
	Update(root->r);Update(root);
	for(int i = 1;i <= n;i++){
		splay *min = r(i, n)->min;
		Splay(min, NULL);printf("%d", size(root->l));putchar(i == n ? 10 : ' ');
		r(i, size(root->l))->tag = 1;
	}
	//print(root, 0);
	return 0;
}
