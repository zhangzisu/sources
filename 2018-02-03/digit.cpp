#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
long long a, b, c = 1;
int main(){
	freopen("digit.in", "r", stdin);
	freopen("digit.out", "w", stdout);

	scanf("%lld%lld", &a, &b);
	if(a == 0){
		if(b >= 10)return puts("0"), 0;
		for(long long i = 1;i <= b;i++)c *= i;
		printf("%lld\n", c % 10);
	}else{
		if(b - a > 10)return puts("0"), 0;
		for(long long i = a + 1;i <= b;i++){
			c *= (i % 10);
		}
		printf("%lld\n", c % 10);
	}
	return 0;
}