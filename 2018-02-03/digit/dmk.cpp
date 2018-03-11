#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<algorithm>
long long a, b, c = 1;
int main(){
	freopen("digit.in", "w", stdout);
	freopen("digit.out", "w", stdout);

	srand(time(NULL));
	int a = rand(), b = a + rand();
	printf("%d %d\n", a, b);
	return 0;
}