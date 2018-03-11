#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline long long $$() {
    register long long x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 1000010
#include <queue>
int n = $(), k = $();
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
long long m = $$(), p[MAXN];
int stk[MAXN], top, cir[MAXN], inc[MAXN], cnt;
bool vis[MAXN];
void dfs(int x, int fa) {
    stk[++top] = x;
    vis[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (i == fa) continue;
        if(inc[to[i]])continue;
        if (!vis[to[i]]) {
            dfs(to[i], i ^ 1);
        } else {
            do {
                inc[cir[++cnt] = stk[top]] = 1;
            } while (stk[top--] != to[i]);
            stk[++top] = x;
        }
    }
    top--;
}
int ans[MAXN];
void DFS(int x, int fa, int deep, int pos) {
	stk[deep] = x;
	if(deep - m > 0)ans[x] = stk[deep - m];
    else ans[x] = cir[(pos + m - deep - 1) % cnt + 1];
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa) DFS(to[i], x, deep + 1, pos);
}
inline long long dis(int i, int j){
	return i > j ? p[i] - p[j] : p[j] - p[i];
}
int H = 1, T = 0;
int main() {
    for (register int i = 1; i <= n; i++) p[i] = $$();
    memset(head, -1, sizeof(head));
    for (register int i = 1; i <= n; i++) {
    	while(T - H + 1 < k + 1)T++;
    	while(T < n && (p[T + 1] - p[i] < p[i] - p[H]))T++, H++;
    	$(i, p[i] - p[H] >= p[T] - p[i] ? H : T);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt = 0;
            dfs(i, -1);
            for (int i = 1; i <= cnt; i++) {
                ans[cir[i]] = cir[(i + m - 1) % cnt + 1];
                for (int j = head[cir[i]]; ~j; j = next[j]) {
                    if (inc[to[j]]) continue;
                    DFS(to[j], cir[i], 1, i);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    puts("");
    return 0;
}
