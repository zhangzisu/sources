#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 500010
#define EPS 1e-4
int n, t;
float val[MAXN << 2], tag[MAXN << 2];
inline void $(float &x, float y){if(y < x)x = y;}
inline void pushDown(int n){
	$(val[n << 1], tag[n]);$(val[n << 1 | 1], tag[n]);
	$(tag[n << 1], tag[n]);$(tag[n << 1 | 1], tag[n]);
	tag[n] = 1e9;
}
void Build(int n, int l, int r){
	val[n] = tag[n] = 1e9;
	if(l == r)return;
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid);Build(n << 1 | 1, mid + 1, r);
}
void Modify(int n, int l, int r, int L, int R, float v){
	if(l == L && r == R)return (void)($(val[n], v), $(tag[n], v));
	int mid = (l + r) >> 1;pushDown(n);
	if(R <= mid)Modify(n << 1, l, mid, L, R, v);
	else if(L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, v);
	else Modify(n << 1, l, mid, L, mid, v), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	val[n] = std::min(val[n << 1], val[n << 1 | 1]);
}
float Query(int n, int l, int r, int L, int R){
	if(!L || !R)return 0;
	if(l == L && r == R)return val[n];
	int mid = (l + r) >> 1;pushDown(n);
	if(R <= mid)return Query(n << 1, l, mid, L, R);
	if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R);
	return std::min(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
int l[MAXN], r[MAXN], a[MAXN], w[MAXN], p[MAXN], sumw, suma;
inline bool judge(float mid){
	Build(1, 1, t);
	register float ret = 0, val;
	for(int i = 1;i <= n;i++){
		val = -mid * a[p[i]] + w[p[i]];
		if(val < 0)ret += val, val = 0;
		Modify(1, 1, t, 1, std::min(r[p[i]], t), Query(1, 1, t, l[p[i]] - 1, t) + val);
	}
	return ret + Query(1, 1, t, t, t) <= 0;
}
inline bool cmp(const int &a, const int &b){return l[a] < l[b] || (l[a] == l[b] && r[a] < r[b]);}
int main(){
	scanf("%d%d", &n, &t);
	for(int i = 1;i <= n;i++){
		scanf("%d%d%d%d", &l[i], &r[i], &w[i], &a[i]);
		sumw += w[i];suma += a[i];p[i] = i;
	}
	std::sort(p + 1, p + n + 1, cmp);
	register float l = 0, r = 1e9, mid;
	while(r - l > EPS){
		mid = (l + r) / 2;
		if(judge(mid))r = mid;
		else l = mid;
	}
	printf("%.3f\n", (l + r) / 2);
	return 0;
}
