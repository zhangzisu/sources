#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
bool sb[200];
int main(){
	printf("%d %d\n", (1 << 11) + 65, 1 << 10);
	sb[1] = 0;register int l = 1;
	for(int i = 1;i < 12;i++){
		for(int j = 1;j <= l;j++)sb[l + j] = !sb[j];
		l <<= 1;
	}
	for(int i = 1;i <= l;i++)putchar(97 + sb[i]);
	for(int i = 1;i <= 65;i++)putchar(97);
	putchar(10);
	return 0;
}
