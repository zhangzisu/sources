#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstring>
#include<algorithm>
#define MAXN 500010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
double f[MAXN];
int s[MAXN];
void $1(int x){
	s[x] = 1;
	for(int i = head[x];~i;i = next[i]){
		$1(to[i]);
		s[x] += s[to[i]];
	}
}
void $2(int x){
	f[x] = ~head[x] ? 0 : 1;
	for(int i = head[x];~i;i = next[i]){
		$2(to[i]);
		f[x] = std::max(f[x], std::min(f[to[i]], (double)s[to[i]] / (s[x] - 1)));
	}
}
int main(){
	memset(head, -1, sizeof(head));
	register int n = $(), k = $();
	for(int i = 2;i <= n;i++)$($(), i);
	$1(1);$2(1);
	register double ans = 0;
	for(int i = 1;i <= n;i++)if(s[i] > k)ans = std::max(ans, f[i]);
	printf("%lf\n", ans);
	return 0;
}
