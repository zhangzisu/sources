#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cassert>
#define MAXN 5010
char buf[MAXN];
int n, stk[MAXN];
long long x;

int son[MAXN][10], fail[MAXN], size[MAXN], cnt = 1;
inline void insert(char *buf){
	int p = 1;
	for(int _i = 0;buf[_i];_i++){
		int i = buf[_i] ^ 48;
		if(!son[p][i])son[p][i] = ++cnt;
		p = son[p][i];
	}
	size[p] = 1;
}
int Q[MAXN], H, T;
inline void build(){
	fail[Q[H = T = 0] = 1] = 0;
	for(int i = 0;i < 10;i++)son[0][i] = 1;
	while(H <= T){
		int now = Q[H++];
		for(int i = 0;i < 10;i++){
			int &s = son[now][i];
			if(!s){
				s = son[fail[now]][i];
			}else{
				fail[s] = son[fail[now]][i];
				Q[++T] = s;
			}
		}
	}
}

long long f[MAXN][MAXN][2];

long long dfs(int pos, int st, int ok, int end){
	assert(st && st <= cnt);
	assert(ok <= 1);
	assert(end <= 1);
	if(!pos)return ok;
	if(~f[pos][st][ok] && !end) return f[pos][st][ok];
	long long ret = 0; int limit = end ? stk[pos] : 9;
	for(int i = 0;i <= limit;i++)
		ret += dfs(pos - 1, son[st][i], ok || size[son[st][i]], end && i == limit);
	if(!end)f[pos][st][ok] = ret;
	assert(ret >= 0);
	return ret;
}

inline long long calc(long long x){
	register int top = 0;
	while(x)stk[++top] = x % 10, x /= 10;
	return dfs(top, 1, size[1], 1);
}

inline int fuck(long long x){
	int fucked = 0;
	while(x)fucked++, x /= 10;
	return fucked;
}

int main(){
	#ifndef DEBUG
	freopen("python.in" , "r", stdin );
	freopen("python.out", "w", stdout);
	#endif
	memset(f, -1, sizeof(f));
	scanf("%s%lld", buf + 1, &x); n = strlen(buf + 1);
	insert(buf + 1); build();

	long long l = n, r = n + fuck(x), ans;
	while(l <= r){
		long long mid = (l + r) >> 1;
		long long fucker = dfs(mid, 1, size[1], 0);
		if(fucker >= x)ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	long long m = ans;
	for(int i = m;i;i--){
		l = 0, r = 9;
		while(l <= r){
			int mid = (l + r) >> 1;
			stk[i] = mid;
			for(int j = i - 1;j;j--)stk[j] = 9;
			long long fucker = dfs(m, 1, size[1], 1);
			if(fucker >= x)ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		stk[i] = ans;
	}
	for(int i = m;i;i--)printf("%d", stk[i]);
	puts("");

	fclose(stdin); fclose(stdout);
	return 0;
}
