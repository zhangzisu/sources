#include<cstdio>
long long a, b;
int main(){
	scanf("%lld%lld", &a, &b);
	register int ret = 0;
	while(a <= b){
		ret++;a*=2;
	}
	printf("%d\n", ret);
	return 0;
}