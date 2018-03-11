#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<ctime>
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
	puts("1000000");
	srand(time(NULL));
	for(int i=0;i<1000000;i++)putchar(rand()%2+'0');
	putchar(10);
}
