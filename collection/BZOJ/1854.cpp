#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 10010
#define MAXM 1000010
int n = $(), head[MAXN], to[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
int match[MAXM], vis[MAXM], time;
bool $(int x){
	for(register int i = head[x];~i;i = next[i]){
		int &t = to[i];
		if(vis[t] == time)continue;vis[t] = time;
		if(!~match[t] || $(match[t])){
			match[t] = x;
			return 1;
		}
	}
	return 0;
}
int main(){
	memset(head, -1, sizeof(head));
	memset(match, -1, sizeof(match));
	for(register int i = 1;i <= n;i++)$($(), i), $($(), i);
	for(int i = 1;i <= n;i++){
		++time;
		if(!$(i)){	
			printf("%d\n", i - 1);
			return 0;
		}
	}
	printf("%d\n", n);
	return 0;
}
