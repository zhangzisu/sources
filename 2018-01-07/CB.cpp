#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 610
#define MAXM 300010
#include<queue>
int head[MAXN], to[MAXM], next[MAXM], val[MAXM], tot = 0;
inline void $(int u, int v, int w){next[tot]  = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;}
int n = $(), k1 = $(), k2 = $();
int dis[MAXN], inq[MAXN], qnt[MAXN], ans, res;
std::queue<int> Q;
inline void SPFA() {
    memset(dis, 0x7F, sizeof(dis));
    inq[1] = qnt[1] = 1;dis[1] = 0;Q.push(1);
    while (Q.size()) {
        int x = Q.front();Q.pop();inq[x] = 0;
        for (int i = head[x]; ~i; i = next[i]) {
            if (dis[to[i]] > dis[x] + val[i]) {
                dis[to[i]] = dis[x] + val[i];
                if (!inq[to[i]]){
                	if(++qnt[to[i]] > n)puts("-1"), exit(0);
                	inq[to[i]] = 1, Q.push(to[i]);
				}
            }
        }
    }
}
int main(){
	memset(head, -1, sizeof(head));
	while(k1--){
		int a = $(), b = $();
		$(a, b, 1);
		$(b, a, -1);
	}
	while(k2--){
		int a = $(), b = $();
		$(b, a, 0);
	}
	SPFA();
	for(int i = 1;i <= n;i++)ans = std::max(ans, dis[i]), res = std::min(res, dis[i]);
	printf("%d\n", ans - res + 1);
	return 0;
}
