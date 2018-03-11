#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
inline long long frc(long long x){
	long long ret = 1;
	for(long long i = 2;i <= x;i++)ret *= i;
	return ret;
}
long long C(long long n, long long m){
	return frc(n) / frc(m) / frc(n - m);
}
int main(){
	while(1){
		long long n, m;
		scanf("%lld%lld", &n, &m);
		printf("C(%lld,%lld) = %lld\n", n, m, C(n, m));
	}
	return 0;
}
