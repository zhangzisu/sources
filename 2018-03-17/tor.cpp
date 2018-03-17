#include<cstdio>
#include<cstdlib>
#include<ctime>

int main(){
	srand(time(NULL));
	printf("%d %d %d %d %d %d %d\n", rand(), rand(), rand(), rand(), rand(), rand(), rand());
	for(int i = 0;i < 100000;i++)putchar(rand()%10+'0');
}
