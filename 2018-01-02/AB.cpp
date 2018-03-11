#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<cstdio>
#include<cctype>
#define BUF 65536
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $() {
	register int x = 0, f = 0; register char ch = gc();
	while (!isdigit(ch) && (ch ^ 45))ch = gc();
	if (!(ch ^ 45))f = 1, ch = gc();
	for (; isdigit(ch); ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1000010
int n, m, a[MAXN], ans;
long long s[MAXN], k;
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++)scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
	for(int i = 1;i <= m;i++){
		scanf("%lld", &k);
		ans = 0;
		for(int i = 1;i <= n;i++){
			for(int j = i;j <= n;j++){
				if(s[j] - s[i - 1] >= k * (j - i + 1))ans = std::max(ans, j - i + 1);
			}
		}
		printf("%d ", ans);
	}
	puts("");
	return 0;
}
