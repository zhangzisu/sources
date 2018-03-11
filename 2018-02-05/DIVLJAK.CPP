#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define MAXN 2000010
#define SIGMA 26
struct state {
    int son[SIGMA], fail, pos;
    inline state() {
        memset(son, 0, sizeof(son));
        fail = 0; pos = -1;
    }
    inline int &operator[](int index) { return son[index]; }
} acm[MAXN];
int root = 0, cnt = 0;
inline void insert(const char *s, int pos) {
    int p = root;
    for (int i = 0; s[i]; i++) {
        const int x = s[i] - 'a';
        if (!acm[p][x]) acm[p][x] = ++cnt;
        p = acm[p][x];
    }
	acm[p].pos = pos;
}
std::queue<int> Q;
inline void build() {
    acm[root].fail = root;
    for (int i = 0; i < SIGMA; i++)
        if (acm[root][i]) Q.push(acm[root][i]);
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < SIGMA; i++) {
            int &s = acm[x][i];
            if (!s)
                s = acm[acm[x].fail][i];
            else
                acm[s].fail = acm[acm[x].fail][i], Q.push(s);
        }
    }
}
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
inline void $(int u, int v){
    next[tot] = head[u]; to[tot] = v; head[u] = tot++;
    next[tot] = head[v]; to[tot] = u; head[v] = tot++;
}
int n, q, t, data[MAXN], vis[MAXN], deep[MAXN], fa[MAXN][21];
int dfn[MAXN], pos[MAXN], bit[MAXN], tim;
inline int lowbit(int x){return x & -x;}
inline void add(int x, int p){
    for(;p <= cnt;p += lowbit(p))bit[p] += x;
}
inline int qry(int p){
    register int ret = 0;
    for(;p;p -= lowbit(p))ret += bit[p];
    return ret;
}
void dp(int x){
    pos[dfn[x] = ++tim] = x;
    for(int i = head[x];~i;i = next[i]){
        if(to[i] != fa[x][0]){
            fa[to[i]][0] = x;
            deep[to[i]] = deep[x] + 1;
            dp(to[i]);
        }
    }
}
inline int lca(int u, int v){
    if(deep[u] < deep[v])std::swap(u, v);
    register int delta = deep[u] - deep[v];
    for(int i = 20;~i;i--)if((delta >> i) & 1)u = fa[u][i];
    for(int i = 20;~i;i--)if(fa[u][i] != fa[v][i])u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
char buf[MAXN];

std::vector<int> V;
int main() {
	memset(head, -1, sizeof(head));

    scanf("%d", &n);
	for(int i = 1;i <= n;i++){
		scanf("%s", buf);
		insert(buf, i);
	}
    for(int i = 1;i <= cnt;i++)$(acm[i].link, i);
    dp(0);

    for(int d = 1;d < 21;d++)for(int i = 0;i <= n;i++)fa[i][d] = fa[fa[i][d - 1]][d - 1];

	scanf("%d", &q);
	for(int i = 1;i <= q;i++){
		scanf("%d", &t);
		if(t & 1){
			scanf("%s", buf);
			int pos = root;
			memset(vis, 0, sizeof(vis));
			for(int i = 0;buf[i];i++){
				V.push_back(dfn[pos = acm[pos][buf[i] - 'a']]);
				if(~acm[pos].pos)vis[acm[pos].pos] = 1;
			}
			std::sort(V.begin(), V.end());
            //
		}else{
			scanf("%d", &t);
			printf("%d\n", data[t]);
		}
	}
    return 0;
}
