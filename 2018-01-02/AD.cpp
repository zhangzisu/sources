#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
int main(){
	srand(time(NULL));
	int n = 1000000, m = 50;
	printf("%d %d\n", n, m);
	for(int i = 1;i <= n;i++)printf("%d ", rand());
	puts("");
	for(int i = 1;i <= m;i++)printf("%d ", rand());
	puts("");
}
