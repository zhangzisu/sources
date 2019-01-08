#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline void pc(char c) { if (_4 == _2 + BUF)fwrite(_2, 1, BUF, stdout), _4 = _2; *_4++ = c; }
inline void rt() {fwrite(_2, 1, _4 - _2, stdout), exit(0);}
inline void pi(int x) {
	static int _5[32];
	if (!x) { pc('0'); return; }
	if (x < 0) { pc(45); x = -x; }
	register int _6; for (_6 = 0; x; x /= 10)_5[++_6] = x % 10; while (_6)pc(_5[_6--] ^ 48);
}
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
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
int n = $(), dfn[MAXN], size[MAXN], tim, top[MAXN], fa[MAXN];
void $1(int x){
	size[x] = 1;
	for(int i = head[x];~i;i = next[i])fa[to[i]] = x, $1(to[i]), size[x] += size[to[i]];
}
void $2(int x){
	dfn[x] = ++tim;if(!~top[x])top[x] = x;
	int huge = n;
	for(int i = head[x];~i;i = next[i])if(size[to[i]] > size[huge])huge = to[i];
	if(huge != n){
		top[huge] = top[x];
		$2(huge);
	}
	for(int i = head[x];~i;i = next[i])if(to[i] != huge)$2(to[i]);
}
int cnt[MAXN << 2], lt[MAXN << 2];
inline void pushDown(int n, int l, int r){
	if(!~lt[n])return;
	int mid = (l + r) >> 1;
	cnt[n << 1] = (mid - l + 1) * (lt[n << 1] = lt[n]);
	cnt[n << 1 | 1] = (r - mid) * (lt[n << 1 | 1] = lt[n]);
	lt[n] = -1;
}
inline void pushUp(int n){
	cnt[n] = cnt[n << 1] + cnt[n << 1 | 1];
}
int Query(int n, int l, int r, int p){
	if(l == r)return cnt[n];
	int mid = (l + r) >> 1;
	pushDown(n, l, r);
	if(p <= mid)return Query(n << 1, l, mid, p);
	else return Query(n << 1 | 1, mid + 1, r, p);
}
int Query(int n, int l, int r, int L, int R){
	if(l == L && r == R)return cnt[n];
	int mid = (l + r) >> 1;
	pushDown(n, l, r);
	if(R <= mid)return Query(n << 1, l, mid, L, R);
	else if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R);
	else return Query(n << 1, l, mid, L, mid) + Query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
void Modify(int n, int l, int r, int L, int R, int val){
	if(l == L && r == R){
		lt[n] = val;
		cnt[n] = (r - l + 1) * val;
		return;
	}
	int mid = (l + r) >> 1;
	pushDown(n, l, r);
	if(R <= mid)Modify(n << 1, l, mid, L, R, val);
	else if(L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, val);
	else Modify(n << 1, l, mid, L, mid, val), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, val);
	pushUp(n);
}
inline void install(int x){
	if(Query(1, 1, n, dfn[x]) == 1){pc('0');pc(10);return;}
	register int sum = 0;
	while(~x){
		sum += dfn[x] - dfn[top[x]] + 1 - Query(1, 1, n, dfn[top[x]], dfn[x]);
		Modify(1, 1, n, dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
	pi(sum);pc(10);
}
inline void uninstall(int x){
	if(Query(1, 1, n, dfn[x]) == 0){pc('0');pc(10);return;}
	pi(Query(1, 1, n, dfn[x], dfn[x] + size[x] - 1));pc(10);
	Modify(1, 1, n, dfn[x], dfn[x] + size[x] - 1, 0);
}
int main(){
	memset(head, -1, sizeof(head));
	memset(top, -1, sizeof(top));
	memset(lt, -1, sizeof(lt));
	for(register int i = 1;i < n;i++)$($(), i);
	$1(0);$2(0);fa[0] = -1;
	register int _ = $();
	while(_--){
		if(ga() == 'i')install($());
		else uninstall($());
	}
	rt();
}
