#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
int n, m;
int main(){
	scanf("%d%d", &n, &m);
	if(n == 1)return puts("1"), 0;
	m = std::min(m, n - m + 1);;
	printf("%d\n", m << 1);
	return 0;
}
