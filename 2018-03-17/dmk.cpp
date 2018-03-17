#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cassert>

int main(int argv, char **argc){
	assert(argv > 1);
	int seed, n, k; sscanf(argc[1], "%d", &seed);
	srand(time(NULL) + seed);
	printf("%d %d %d %d\n", rand()&1, rand()&1, rand()&1, rand()&1);
	//puts("0 0 0 1");
	printf("%d %d\n", n = 1000, k = 18);
	for(int i = 1;i <= n;i++)printf("%d\n", rand());
}
