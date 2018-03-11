#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0, f = 0;register char ch = gc();
	while(!isdigit(ch) && (ch ^ 45))ch = gc();
	if(!(ch ^ 45))f = 1, ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
inline long long $$(){
	register long long x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
const long long MAX = (~(unsigned long long)0) >> 1;
const long long MIN = ~(unsigned long long)0;
int _ = $(), n, m, c[2][MAXN];
long long t[2][MAXN], max, min, cur1, cur2;
int main(){
	while(_--){
		n = $();cur1 = 0;max = MIN;
		for(int i = 1;i <= n;i++){
			c[0][i] = $(), t[0][i] = $();
			cur1 += t[0][i] * c[0][i];
			max = std::max(max, cur1);
		}
		m = $();cur2 = 0;min = MAX;
		for(int i = 1;i <= n;i++){
			c[1][i] = $(), t[1][i] = $();
			cur2 += t[1][i] * c[1][i];
			min = std::min(min, cur2);
		}
		//cur1 = cur2 = 0;
		for(int i = 0;i <= max - min;i++){
			cur1 = 0;
			cur2 = cur1 + i;
			for(int i = 1;i <= n;i++){
				if(cur1)
			}
		}
	}
	return 0;
}
