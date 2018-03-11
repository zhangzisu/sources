#include<algorithm>
#include<cstdio>
#include<map>
typedef long long LL;
typedef std::pair<LL, LL> PL;
std::map<PL, PL> M;
LL n;
PL dfs(LL n, int m){
	if(n <= 0)return PL(0, n);
	PL x = PL(n, m);
	if(!M.count(x)){
		LL a = 1;
		while(a <= n / 10)a *= 10;
		int r = n / a;
		PL rt = PL(0, n % a);
		while(r > 0 || rt.second > 0){
			PL tmp = dfs(rt.second, std::max(m, r));
			rt.first += tmp.first;
			rt.second = tmp.second;
			if(r && !rt.second){rt.first++;rt.second -= std::max(m, r);}
			if(r && rt.second){r--;rt.second += a;}
		}
		M[x] = rt;
	}
	return M[x];
}
int main(){
	scanf("%I64d", &n);
	printf("%I64d\n", dfs(n, 0).first);
	return 0;
}
