#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MOD 1000000007
int bit[10], b[60][10], f[2][5][300000];
inline void $(int &a, const int &b){a = (long long)(a + b) % MOD;}
inline int get(const int &x, const int &pos){return (x % bit[pos]) / bit[pos - 1];}
inline int set(const int &x, const int &pos, const int &val){return val ? x + val * bit[pos - 1] : x;}
int main(){
	register int n = $(), m = $(), k = $();
	bit[0] = 1;
	for(int i = 1;i < 10;i++)bit[i] = bit[i - 1] * 6;
	while(k--)b[$() + 1][$() + 1] = 1;
	int now = 1, pre = 0;
	f[now][0][0] = 1;
	for(register int i = 1;i <= n;i++){
		std::swap(now, pre);
		memset(f[now], 0, sizeof(f[now]));
		for(register int k = 0;k < bit[m];k++)$(f[now][0][k], f[pre][0][k]);
		for(register int j = 1;j <= m;j++){
			std::swap(now, pre);
			memset(f[now], 0, sizeof(f[now]));
			for(register int k = 0;k < bit[m];k++){
				for(register int l = 0;l < 5;l++){
					if(b[i][j]){
						if(l || get(k, j))continue;
						$(f[now][l][k - get(k, j)], f[pre][l][k]);
					}else{
						register int last = f[pre][l][k];
						register int cur = get(k, j);
						register int mask = k - cur * bit[j - 1];
						if(!l){
							if(!cur){
								$(f[now][0][set(mask, j, 3)], last);
								$(f[now][1][set(mask, j, 5)], last);
								$(f[now][2][set(mask, j, 1)], last);
								$(f[now][3][set(mask, j, 0)], last);
							}else if(cur == 1){
								$(f[now][0][set(mask, j, 0)], last);
							}else if(cur == 2){
								$(f[now][0][set(mask, j, 1)], last);
								$(f[now][1][set(mask, j, 0)], last);
							}else if(cur == 3){
								$(f[now][0][set(mask, j, 2)], last);
								$(f[now][1][set(mask, j, 1)], last);
								$(f[now][4][set(mask, j, 0)], last);
							}else if(cur == 4){
								$(f[now][0][set(mask, j, 1)], last);
								$(f[now][1][set(mask, j, 0)], last);
							}else if(cur == 5){
								$(f[now][0][set(mask, j, 1)], last);
							}
						}else if(!cur){
							if(l == 1){
								$(f[now][0][set(mask, j, 0)], last);
							}else if(l == 2){
								$(f[now][0][set(mask, j, 1)], last);
								$(f[now][1][set(mask, j, 0)], last);
							}else if(l == 3){
								$(f[now][0][set(mask, j, 4)], last);
								$(f[now][1][set(mask, j, 1)], last);
								$(f[now][2][set(mask, j, 0)], last);
							}else if(l == 4){
								$(f[now][0][set(mask, j, 1)], last);
								$(f[now][1][set(mask, j, 0)], last);
							}
						}else if(cur == 3 && l == 2){
							$(f[now][0][set(mask, j, 0)], last);
						}else if(cur == 2 && l == 3){
							$(f[now][0][set(mask, j, 0)], last);
						}else if(cur == 3 && l == 3){
							$(f[now][0][set(mask, j, 1)], last);
							$(f[now][1][set(mask, j, 0)], last);
						}else if(cur == 5 && l == 3){
							$(f[now][0][set(mask, j, 0)], last);
						}
					}
				}
			}
		}
	}
	printf("%d\n", f[now][0][0]);
	return 0;
}
