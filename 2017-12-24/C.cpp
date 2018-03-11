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
#define MAXN 200010
#define ULL unsigned long long
#include<vector>
ULL val[MAXN << 5][4];
int L[MAXN << 5], R[MAXN << 5], tot = 0, root[MAXN];
struct node{
	int x, y, s;
	inline node(int x = 0, int y = 0, int s = 0):x(x), y(y), s(s){}
	inline friend bool operator < (const node &a, const node &b){
		return a.x < b.x;
	}
};
inline void pushUp(int n){
	for(int i = 0;i < 4;i++)val[n][i] = val[L[n]][i] + val[R[n]][i];
}
int Insert(int n, int l, int r, int p, ULL v0, ULL v1, ULL v2, ULL v3){
	int cur = ++tot;
	if(l == r){
		memcpy(val[cur], val[n], sizeof(val[cur]));
		val[cur][0] += v0;val[cur][1] += v1;
		val[cur][2] += v2;val[cur][3] += v3;
		return cur;
	}
	L[cur] = L[n];R[cur] = R[n];int mid = (l + r) >> 1;
	if(p <= mid)L[cur] = Insert(L[n], l, mid, p, v0, v1, v2, v3);
	else R[cur] = Insert(R[n], mid + 1, r, p, v0, v1, v2, v3);
	pushUp(cur);
	return cur;
}
void Query(int n, int l, int r, int _l, int _r, ULL &v0, ULL &v1, ULL &v2, ULL &v3){
	if(!n)return;
	if(l == _l && r == _r){
		v0 += val[n][0];v1 += val[n][1];
		v2 += val[n][2];v3 += val[n][3];
		return;
	}
	int mid = (l + r) >> 1;
	if(_r <= mid)Query(L[n], l, mid, _l, _r, v0, v1, v2, v3);
	else if(_l > mid)Query(R[n], mid + 1, r, _l, _r, v0, v1, v2, v3);
	else Query(L[n], l, mid, _l, mid, v0, v1, v2, v3), Query(R[n], mid + 1, r, mid + 1, _r, v0, v1, v2, v3);
}
std::vector<node> V;
int N = $(), M = $();
inline ULL Query(int x, int y){
	if(!x || !y)return 0;
	ULL v0 = 0, v1 = 0, v2 = 0, v3 = 0;
	int pos = std::upper_bound(V.begin(), V.end(), node(x)) - V.begin();
	Query(root[pos], 1, M + 5, 1, y, v0, v1, v2, v3);
	return v3 - v2 * (x + 1) - v1 * (y + 1) + v0 * (x + 1) * (y + 1);
}
ULL ans = 0;
int main(){
	register int W = $(), q = $();
	for(int i = 1;i <= W;i++){
		int l = $(), r = $(), d = $(), u = $(), s = $();
		V.push_back(node(l, d, s));V.push_back(node(r + 1, u + 1, s));
		V.push_back(node(l, u + 1, -s));V.push_back(node(r + 1, d, -s));
	}
	std::sort(V.begin(), V.end());
	for(unsigned i = 0;i < V.size();i++)
		root[i + 1] = Insert(root[i], 1, M + 5, V[i].y, V[i].s, (ULL)V[i].s * V[i].x, (ULL)V[i].s * V[i].y, (ULL)V[i].s * V[i].x * V[i].y);
	while(q--){
		int x = $(), y = $();
		int l = ans % N + 1;
		int r = (ans + x) % N + 1;
		if(l > r)std::swap(l, r);
		int d = ans % M + 1;
		int u = (ans + y) % M + 1;
		if(d > u)std::swap(u, d);
		printf("%llu\n", ans = Query(r, u) - Query(l - 1, u) - Query(r, d - 1) + Query(l - 1, d - 1));
	}
	return 0;
}
