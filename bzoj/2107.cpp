#include<cstdio>
#include<cctype>
#include<cstdarg>
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
inline int max(int n, ...){
	register int ret = 0x80000000;
	register va_list args;va_start(args, n);
	while(n--)ret = std::max(ret, va_arg(args, int));
	va_end(args);
	return ret;
}
#define MAXN 3010
int a[MAXN], b[MAXN], f[MAXN][MAXN][3], d[4][4], A, B;
int main(){
	register char ch = gc();register int n, m;
	while(!isalpha(ch))ch = gc();
	for(n = 1;isalpha(ch);ch = gc(), n++)
		switch(ch){case 'A':a[n] = 0;break;case 'T':a[n] = 1;break;case 'G':a[n] = 2;break;case 'C':a[n] = 3;break;}
	while(!isalpha(ch))ch = gc();
	for(m = 1;isalpha(ch);ch = gc(), m++)
		switch(ch){case 'A':b[m] = 0;break;case 'T':b[m] = 1;break;case 'G':b[m] = 2;break;case 'C':b[m] = 3;break;}
	for(int i = 0;i < 4;i++)for(int j = 0;j < 4;j++)d[i][j] = $();
	A = -$();B = -$();
	for(int i = 0;i <= n;i++)for(int j = 0;j <= m;j++)f[i][j][0] = f[i][j][1] = f[i][j][2] = -0x3F3F3F3F;
	f[0][0][0] = 0;n--;m--;
	for(int i = 0;i <= n;i++)
		for(int j = 0;j <= m;j++){
			if(i && j)f[i][j][0] = max(3, f[i - 1][j - 1][0], f[i - 1][j - 1][1], f[i - 1][j - 1][2]) + d[a[i]][b[j]];
			if(i)f[i][j][1] = max(2, f[i - 1][j][1] + B, max(2, f[i - 1][j][0], f[i - 1][j][2]) + A);
			if(j)f[i][j][2] = max(2, f[i][j - 1][2] + B, max(2, f[i][j - 1][0], f[i][j - 1][1]) + A);
		}
	printf("%d\n", max(3, f[n][m][0], f[n][m][1], f[n][m][2]));
}
