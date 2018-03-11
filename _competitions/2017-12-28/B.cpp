#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 10485760
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 1000010
int g[MAXN][20], m[MAXN][20], n = $();
inline int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
inline bool qry(int l, int r){
	int d = log((double)r - l + 1) / log(2);
	return std::min(m[l][d], m[r - (1 << d) + 1][d]) == gcd(g[l][d], g[r - (1 << d) + 1][d]);
}
int main(){
	for(int i = 1;i <= n;i++)g[i][0] = m[i][0] = $();
	for(int d = 1;d < 20;d++){
		for(int i = 1;i <= n;i++){
			if(i + (1 << (d - 1)) > n)break;
			m[i][d] = std::min(m[i][d - 1], m[i + (1 << (d - 1))][d - 1]);
			g[i][d] = gcd(g[i][d - 1], g[i + (1 << (d - 1))][d - 1]);
		}
	}
	register int q = $();
	while(q--){
		int l = $() + 1, r = $();
		puts(qry(l, r) ? "Yes" : "No");
	}
	return 0;
}
