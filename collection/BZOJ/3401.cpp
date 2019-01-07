#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int n, h[MAXN], a[MAXN], stk[MAXN], top;
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)scanf("%d", &h[i]);
	h[0] = 0x3F3F3F3F;
	stk[top = 0] = 0;
	for(int i = n;i >= 1;i--){
		while(top && h[stk[top]] <= h[i])top--;
		a[i] = stk[top];
		stk[++top] = i;
	}
	for(int i = 1;i <= n;i++)printf("%d\n", a[i]);
	return 0;
}
