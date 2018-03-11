#pragma GCC optimize("O2")
#include<cstdio>
#include<cctype>
inline long long $(){
	register long long x = 0, f = 0; register char ch = getchar();
	while(!isdigit(ch) && (ch ^ 45))ch = getchar();
	if(!(ch ^ 45))ch = getchar(), f = 1;
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#define MAXN 100010
const long long MAX = (~0ULL) >> 1;
const long long MIN = ~0LL;
long long n, m, q, ans = MAX, k = 0;
long long sum, tmp, b[MAXN], a[MAXN];
int main(){
	n = $(); m = $(); q = $();
	for(long long i = 1;i <= n;i++)sum += (i & 1 ? 1 : -1) * $();
	for(long long j = 1;j <= m;j++)b[j] = $();
	for(long long i = 1;i <= n;i++)tmp += (i & 1 ? 1 : -1) * b[i];
	a[++k] = MIN; a[++k] = MAX; a[++k] = tmp;
	for(long long i = n + 1;i <= m;i++){
		tmp -= b[i - n];
		tmp = -tmp;
		tmp += (n & 1 ? 1 : -1) * b[i];
		a[++k] = tmp;
	}
	std::sort(a + 1, a + k + 1);
	int pos = std::lower_bound(a + 1, a + k + 1, sum) - a;
	ans = std::min(ans, std::abs(a[pos] - sum));
	ans = std::min(ans, std::abs(a[pos - 1] - sum));
	printf("%lld\n", ans);
	while(q--){
		long long l = $(), r = $(), x = $();
		ans = MAX;
		long long delta = r - l + 1;
		long long c0 = delta >> 1;
		long long c1 = c0 + (delta & 1);
		sum += c1 * (l & 1 ? 1 : -1) * x;
		sum += c0 * (l & 1 ? -1 : 1) * x;
		int pos = std::lower_bound(a + 1, a + k + 1, sum) - a;
		ans = std::min(ans, std::abs(a[pos] - sum));
		ans = std::min(ans, std::abs(a[pos - 1] - sum));
		printf("%lld\n", ans);
	}
	return 0;
}