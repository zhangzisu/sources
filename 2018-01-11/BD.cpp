#include<ctime>
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
int main(){
	srand(time(NULL));
	int n = 100000, t = 100000;
	printf("%d %d\n", n, t);
	for(int i = 1;i <= n;i++){
		int a = rand() % t + 1;
		int b = a + rand() % (t - a + 1);
		int w = rand() % 1 + 1;
		int c = rand() % 1000 + 1;
		printf("%d %d %d %d\n", a, b, w, c);
	}
}
