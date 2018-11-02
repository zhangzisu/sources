#include<algorithm>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
int n, m;
inline char rc(){
	int x = rand() % 2;
	return x ? rand() % 26 + 'a' : rand() % 26 + 'A';
}
int main(int argc, char **argv){
	int syseed;
	if(argc > 1) sscanf(argv[1], "%d", &syseed);
	srand(time(NULL) + syseed);
	n = 11;
	m = rand()%2+2;
	printf("%d %d\n", n, m);
	int now = 1;
	for(int i = 1;i <= m;i++){
		int t = rand() % 5 + 2;
		if(now * t > 123)t = 1;
		now *= t;
		printf("%c %d\n", rc(), t);
	}
	return 0;
}
