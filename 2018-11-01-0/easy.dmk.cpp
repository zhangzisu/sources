#include<algorithm>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
int n, m;
int main(int argc, char **argv){
	int syseed;
	if(argc > 1) sscanf(argv[1], "%d", &syseed);
	srand(time(NULL) + syseed);
	n = 20000;
	printf("%d\n", n);
	for(int i = 1;i <= n;i++) printf("%d ", rand());
	puts("");
	return 0;
}
