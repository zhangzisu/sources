#include<cstdio>
#include<cstdlib>
int n;
int main(){
	scanf("%d", &n);
	printf("%d\n", n % 4 == 0 || n % 4 == 3 ? 0 : 1);
	printf("%d ", (n / 4) * 2 + (n % 4 ? 1 : 0));
	for(int i = n;i - 4 >= 0;i -= 4)printf("%d %d ", i, i - 3);
	if(n % 4 == 3)puts("3");
	else if(n % 4)puts("1");
	return 0;
}
