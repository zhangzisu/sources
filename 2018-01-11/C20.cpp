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
#define MAXN 1000010
const int MAX = (~(unsigned)0) >> 1;
const int MIN = ~(unsigned)0;
int _ = $(), n, m, t, x, c[2][MAXN], max[2], min[2], cur0, cur1, ans, res;
int main(){
	while(_--){
		n = $();cur0 = 0;max[0] = min[0] = 0;
		for(int i = 1;i <= n;i++){
			x = $();t = $();
			cur0 += (c[0][i] = x);
			max[0] = std::max(max[0], cur0);
			min[0] = std::min(min[0], cur0);
			while(--t){
				cur0 += (c[0][i] = x);
				max[0] = std::max(max[0], cur0);
				min[0] = std::min(min[0], cur0);
				i++;n++;
			}
		}
		m = $();cur1 = 0;max[1] = min[1] = 0;
		for(int i = 1;i <= m;i++){
			x = $();t = $();
			cur1 += (c[1][i] = x);
			max[1] = std::max(max[1], cur1);
			min[1] = std::min(min[1], cur1);
			while(--t){
				cur1 += (c[1][i] = x);
				max[1] = std::max(max[1], cur1);
				min[1] = std::min(min[1], cur1);
				i++;m++;
			}
		}
		res = 0;
		for(int i = min[0] - max[1];i <= max[0] - min[1];i++){
			cur0 = 0;
			cur1 = cur0 + i;
			ans = 0;
			for(int i = 1;i <= n;i++){
				if(cur0 == cur1)ans++;
				if(ans + (n - i) < res)break; 
				cur0 += c[0][i];
				cur1 += c[1][i];
			}
			if(cur0 == cur1)ans++;
			res = std::max(res, ans);
		}
		printf("%d\n", res);
	}
	return 0;
}
