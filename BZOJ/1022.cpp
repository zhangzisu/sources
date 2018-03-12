#include<cstdio>
int t, n, r, a, f;
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);a = 0;f = 1;
		while(n--)scanf("%d", &r), a ^= r, f &= r == 1;
		puts(a ^ f ? "John" : "Brother");
	}
	return 0;
}
