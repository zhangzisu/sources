#include<cstdio>
int a1, a2, a3, a4, a5, a6, a7, a8, ans;
inline void $(int &x, int y){if(y > x)x = y;}
int main(){
	freopen("FUNGHI.IN", "r", stdin);
	freopen("FUNGHI.OUT", "w", stdout);
	
	scanf("%d%d%d%d%d%d%d%d", &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
	$(ans, a1 + a2 + a3 + a4);
	$(ans, a2 + a3 + a4 + a5);
	$(ans, a3 + a4 + a5 + a6);
	$(ans, a4 + a5 + a6 + a7);
	$(ans, a5 + a6 + a7 + a8);
	$(ans, a6 + a7 + a8 + a1);
	$(ans, a7 + a8 + a1 + a2);
	$(ans, a8 + a1 + a2 + a3);
	printf("%d\n", ans);
}