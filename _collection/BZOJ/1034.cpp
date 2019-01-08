#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int n, a[MAXN], b[MAXN];
inline int calc(int *a, int *b){
	register int la = 1, ra = n, lb = 1, rb = n, ans = 0;
	while(la <= ra && lb <= rb){
		if(a[ra] < b[lb])break;
		if(a[la] > b[lb]){
			la++, lb++;
			ans += 2;
			continue;
		}
		if(a[ra] > b[rb]){
			ra--, rb--;
			ans += 2;
			continue;
		}
		if(a[la++] == b[rb--])ans++;
	}
	return ans;
}
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
	for(int i = 1;i <= n;i++)scanf("%d", &b[i]);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	printf("%d %d\n", calc(a, b), (n << 1) - calc(b, a));
	return 0;
} 
