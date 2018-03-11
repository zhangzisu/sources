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
#define MAXN 1000010
int n, m, a[MAXN], s1[MAXN], s2[MAXN];
long long s[MAXN], k;
inline long long G(int x){return s[x] - k * x;}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++)scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
	register int t1, t2, p, ans;
	while(m--){
		scanf("%lld", &k);
		t1 = t2 = p = ans = 0;
		for(int i = 1;i <= n;i++){
			if(G(i) < G(s1[t1]))s1[++t1] = i;
		}
		for(int i = 1;i <= n;i++){
			while(t2 >= 0 && G(i) >= G(s2[t2]))t2--;
			s2[++t2] = i;
		}
		for(int i = 0;i <= t2;i++){
			while(p <= t1 && G(s1[p]) > G(s2[i]))p++;
			if(G(s1[p]) <= G(s2[i]))ans = std::max(ans, s2[i] - s1[p]);
		}
		printf("%d ", ans);
	}
	puts("");
	return 0;
}
