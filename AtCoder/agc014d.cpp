#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0, n = $();
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
	next[tot] = head[v];to[tot] = u;head[v] = tot++;
}
int dp(int x, int fa){
	int cnt = 0;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa)continue;
		cnt += dp(to[i], x);
		if(cnt >= 2)puts("First"), exit(0);
	}
	return !cnt;
}
int main(){
	memset(head, -1, sizeof(head));
	for(int i = 1;i < n;i++)$($(), $());
	if(dp(1, 0))puts("First");
	else puts("Second");
	return 0;
}
