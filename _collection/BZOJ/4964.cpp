#include<cstdio>
#include<algorithm>
#define MAXN 400010
int n, m, a[MAXN], stk[MAXN], f[MAXN], g[MAXN];
char buf[MAXN];
std::pair<int, int> b[MAXN];
int F[MAXN << 2], G[MAXN << 2], V[MAXN << 2];
inline void pushUp(int n){
	V[n] = std::max(V[n << 1], V[n << 1 | 1]);
	F[n] = std::max(F[n << 1], F[n << 1 | 1]);
	G[n] = std::max(G[n << 1], G[n << 1 | 1]);
}
void Build(int n, int l, int r){
	if(l == r){
		V[n] = a[l];F[n] = f[l];G[n] = g[l];
		return;
	}
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid);
	Build(n << 1 | 1, mid + 1, r);
	pushUp(n);
}
int Query(int n, int l, int r, int L, int R, int *V){
	if(l == L && r == R)return V[n];
	int mid = (l + r) >> 1;
	if(R <= mid)return Query(n << 1, l, mid, L, R, V);
	else if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R, V);
	else return std::max(Query(n << 1, l, mid, L, mid, V), Query(n << 1 | 1, mid + 1, r, mid + 1, R, V));
}
int main(){
	scanf("%d%d", &n, &m);n++;
	scanf("%s", buf + 2);
	for(register int i = 2;i <= n;i++)a[i] = a[i - 1] + (buf[i] == ')' ? 1 : -1);
	for(register int i = 1;i <= n;i++)b[i] = std::make_pair(a[i], i);
	std::sort(b + 1, b + n + 1);
	register int top;
	stk[top = 0] = 0;
	for(register int i = 1;i <= n;stk[++top] = i++){
		while(top && a[i] >= a[stk[top]])top--;
		f[i] = i - (*std::upper_bound(b + 1, b + n + 1, std::make_pair(a[i], stk[top]))).second;
	}
	stk[top = 0] = n + 1;
	for(register int i = n;i;stk[++top] = i--){
		while(top && a[i] >= a[stk[top]])top--;
		g[i] = (*(std::lower_bound(b + 1, b + n + 1, std::make_pair(a[i], stk[top])) - 1)).second - i;
	}
	Build(1, 1, n);
	top = m;
	while(top--){
		int x, y;scanf("%d%d", &x, &y);y++;
		int max = Query(1, 1, n, x, y, V);
		int l = (*std::lower_bound(b + 1, b + n + 1, std::make_pair(max, x))).second;
		int r = (*(std::upper_bound(b + 1, b + n + 1, std::make_pair(max, y)) - 1)).second;
		int ans = r - l;
		if(l > x)ans = std::max(ans, Query(1, 1, n, x, l - 1, G));
		if(r < y)ans = std::max(ans, Query(1, 1, n, r + 1, y, F));
		printf("%d\n", ans);
	}
	return 0;
}
