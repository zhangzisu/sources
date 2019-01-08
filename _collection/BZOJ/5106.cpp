#include<cstdio>
#include<algorithm>
#define MAXN 200010
int n;
long long s, t, h[MAXN], a[MAXN];
inline bool judge(long long mid){
	long long sum = 0;
	for(int i = 1;i <= n;i++){
		if(h[i] + a[i] * mid >= t)sum += h[i] + a[i] * mid;
		if(sum >= s)return 1;
	}
	return 0;
}
int main(){
	scanf("%d%lld%lld", &n, &s, &t);
	for(int i = 1;i <= n;i++)scanf("%d", &h[i]);
	for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
	register long long l = 0, r = std::max(s, t), mid, ans = -1;
	while(l <= r){
		mid = (l + r) >> 1;
		if(judge(mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
}
