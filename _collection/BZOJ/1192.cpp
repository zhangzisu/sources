#include<cstdio>
#include<cmath>
int main(){
	long long a;scanf("%lld", &a);
	int b = log((double)a) / log((double)2);
	if((1LL << b) < a)b++;
	printf("%d\n", b);
	return 0;
}
