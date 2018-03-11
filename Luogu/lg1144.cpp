#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include<queue>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1000010
#define MAXM 2000010
#define MOD 100003
int n = $(), m = $(), head[MAXN], next[MAXM], to[MAXM], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u];to[tot] = v;head[u] = tot++;
}
int dis[MAXN], cnt[MAXN], inq[MAXN];
std::queue<int> Q;
inline void $1(int s){
	memset(dis, 0x3F, sizeof(dis));cnt[s] = 1;
	Q.push(s);dis[s] = 0;inq[s] = 1;
	while(Q.size()){
		int t = Q.front();Q.pop();inq[t] = 0;
		for(int i = head[t];~i;i = next[i]){
			if(dis[to[i]] > dis[t] + 1){
				dis[to[i]] = dis[t] + 1;
				cnt[to[i]] = cnt[t];
				if(!inq[to[i]])Q.push(to[i]), inq[to[i]] = 1;
			}else if(dis[to[i]] == dis[t] + 1){
				cnt[to[i]] += cnt[t];
				cnt[to[i]] %= MOD;
			}
		}
	}
}
int main(){
	memset(head, -1, sizeof(head));
	while(m--){
		int $1 = $(), $2 = $();
		$($1, $2);$($2, $1);
	}
	$1(1);
	for(int i = 1;i <= n;i++)printf("%d\n", cnt[i]);
	return 0;
}
