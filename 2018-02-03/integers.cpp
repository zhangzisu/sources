#include<set>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int n, m, t = 0x3F3F3F3F, ans = 0x3F3F3F3F;
std::set<int> S;
int main(){
	freopen("integers.in", "r", stdin);
	freopen("integers.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for(int i = 1, x;i <= n;i++){
		scanf("%d", &x);
		S.insert(x);
	}
	for(int i = 1, x;i <= m;i++){
		scanf("%d", &x);
		if(S.count(x))ans = std::min(ans, x);
		t = std::min(t, x);
	}
	if(ans == 0x3F3F3F3F){
		ans = std::min(*S.begin() * 10 + t, t * 10 + *S.begin());
	}
	printf("%d\n", ans);
	return 0;
}