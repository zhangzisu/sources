#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200010
int n = $(), a[MAXN], root = 0, m;
long double ans = 0;
long long sum[MAXN << 4];
int val[MAXN << 4], L[MAXN << 4], R[MAXN << 4], cnt;
inline void pushUp(int n){
	sum[n] = sum[L[n]] + sum[R[n]];
	val[n] = val[L[n]] + val[R[n]];
}
inline void Insert(int &n, int l, int r, int v){
	if(!n)n = ++cnt;
	if(l == r){
		sum[n] += v;
		val[n]++;
		return;
	}
	int mid = (l + r) >> 1;
	if(v <= mid)Insert(L[n], l, mid, v);
	else Insert(R[n], mid + 1, r, v);
	pushUp(n);
}
struct answer{
	long long sum;int val;
	inline answer(long long sum = 0, int val = 0):sum (sum), val (val){}
	inline friend answer operator + (const answer &a, const answer &b){
		return answer(a.sum + b.sum, a.val + b.val);
	}
};
inline answer Upper(int n, int l, int r, int v){
	if(!n)return answer(0, 0);
	if(l >= v)return answer(sum[n], val[n]);
	int mid = (l + r) >> 1;
	if(v > mid)return Upper(R[n], mid + 1, r, v);
	return Upper(L[n], l, mid, v) + Upper(R[n], mid + 1, r, v);
}
inline answer Lower(int n, int l, int r, int v){
	if(!n)return answer(0, 0);
	if(r <= v)return answer(sum[n], val[n]);
	int mid = (l + r) >> 1;
	if(v <= mid)return Lower(L[n], l, mid, v);
	return Lower(L[n], l, mid, v) + Lower(R[n], mid + 1, r, v);
}
int main(){
	for(int i = 1;i <= n;i++)m = std::max(m, a[i] = $());
	for(int i = n;i;i--){
		answer lower = Lower(root, 1, m, a[i] - 2);
		ans += lower.sum;ans -= (long double)a[i] * lower.val;
		answer upper = Upper(root, 1, m, a[i] + 2);
		ans += upper.sum;ans -= (long double)a[i] * upper.val;
		Insert(root, 1, m, a[i]);
	}
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0) << ans << std::endl;
	return 0;
}
