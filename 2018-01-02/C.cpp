#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<cstdio>
#include<cctype>
#define BUF 1024768
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $() {
	register int x = 0; register char ch = gc();
	while (!isdigit(ch))ch = gc();
	for (; isdigit(ch); ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 100010
int n, m, a[MAXN], c, f[MAXN];
struct ll{
	ll*pre, *next;
	int d;
	inline ll(int d = 0):pre(NULL), next(NULL), d(d){}
}*tail, *d[MAXN];
inline void del(ll *x){
	if(!x)return;
	if(x->pre)x->pre->next = x->next;
	if(x->next)x->next->pre = x->pre;
	else tail = x->pre;
}
inline ll* insert(int x){
	if(!tail){tail = new ll(x);return tail;}
	tail->next = new ll(x);
	tail->next->pre = tail;
	return tail = tail->next;
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++){
		scanf("%d", &a[i]);
		del(d[a[i]]);d[a[i]] = insert(i);
		f[i] = 0x3F3F3F3F;
		c = 0;
		for(ll* x = tail;x;x = x->pre){
			c++;if(c * c > i)goto fail;
			f[i] = std::min(f[i], (x->pre ? f[x->pre->d] : 0) + c * c);
		}
		f[i] = std::min(f[i], c * c);
		fail:;
	}
	printf("%d\n", f[n]);
	return 0;
}
