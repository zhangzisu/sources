#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
int main(){
	register int n = $(), ans = 0;
	for(int i = 1;i <= n;i++)ans += n / i;
	printf("%d\n", ans);
	return 0;
}
