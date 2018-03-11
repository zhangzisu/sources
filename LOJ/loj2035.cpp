#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 3010
int Q[MAXN], cur;
long long s[MAXN], f[2][MAXN];
inline long long A(int j, int k){return f[!cur][j] - f[!cur][k] + s[j] * s[j] - s[k] * s[k];}
inline long long B(int j, int k){return (s[j] - s[k]) * 2;}
int main(){
	register int n = $(), m = $(), H, T;
	std::fill(f[0] + 1, f[0] + n + 1, 0x3F3F3F3F3F3F);
	for(int i = 1;i <= n;i++)s[i] = s[i - 1] + $();
	for(int i = 1;i <= m;i++){
		Q[H = T = 0] = 0;cur = i & 1;
		for(int j = 1;j <= n;j++){
			while(H < T && A(Q[H + 1], Q[H]) <= s[j] * B(Q[H + 1], Q[H]))H++;
			f[cur][j] = f[!cur][Q[H]] + (s[j] - s[Q[H]]) * (s[j] - s[Q[H]]);
			while(H < T && A(j, Q[T]) * B(Q[T], Q[T - 1]) <= A(Q[T], Q[T - 1]) * B(j, Q[T]))T--;
			Q[++T] = j;
		}
	}
	printf("%lld\n", f[cur][n] * m - s[n] * s[n]);
	return 0;
}
