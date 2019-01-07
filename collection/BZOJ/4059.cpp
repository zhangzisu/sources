#include<cstdio>
#include<cstring>
#include<ext/hash_map>
__gnu_cxx::hash_map<int, int> M;
#define MAXN 200010
int pre[MAXN], next[MAXN], p[MAXN], a[MAXN], t, n;
bool judge(int l, int r){
	if(l >= r)return 1;
	for(int ll = l, rr = r;ll <= rr;ll++, rr--){
		if(pre[ll] < l && next[ll] > r)return judge(l, ll - 1) && judge(ll + 1, r);
		if(pre[rr] < l && next[rr] > r)return judge(l, rr - 1) && judge(rr + 1, r);
	}
	return 0;
}
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		M.clear();memset(next, -1, sizeof(int) * n + 16);
		for(int i = 1;i <= n;i++){
			scanf("%d", &a[i]);
			pre[i] = M.count(a[i]) ? M[a[i]] : -1;
			if(M.count(a[i]))next[M[a[i]]] = i;
			M[a[i]] = i;
		}
		for(int i = 1;i <= n;i++)if(!~next[i])next[i] = n + 1;
		puts(judge(1, n) ? "non-boring" : "boring");
	}
	return 0;
}
