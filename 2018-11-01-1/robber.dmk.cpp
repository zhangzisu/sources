#include<algorithm>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
int n, m;
inline unsigned char randuchar(){
	return rand()&255;
}
inline unsigned short randushort(){
	return randuchar()<<8|randuchar();
}
inline unsigned int randuint(){
	return randushort()<<16|randushort(); 
}
int main(int argc, char **argv){
	int syseed;
	if(argc > 1) sscanf(argv[1], "%d", &syseed);
	srand(time(NULL) + syseed);
	n = 200000;
	m = 400000;
	printf("%d %d\n", n);
	for(int i = 1;i <= n;i++) printf("%d ", rand() % 1000 + 1);
	for(int i = 1;i <= m;i++){
		printf("%d %d\n", randuint()%n+1,randuint()%n+1);
	}
	puts("");
	return 0;
}
