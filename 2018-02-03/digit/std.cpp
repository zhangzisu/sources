#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
long long a, b, c = 1;
int main(){
	freopen("digit.in", "r", stdin);
	freopen("digit.ans", "w", stdout);

	scanf("%lld%lld", &a, &b);
	for(int i = a + 1;i <= b;i++)(c *= i) %= 10;
	printf("%lld\n", c);
	return 0;
}