#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 500010
#define INF 0x3F3F3F3F
const int _s = 16001;
const int _t = 16002;
const int __s = 16003;
const int __t = 16004;
int n, m, t[MAXN], s[MAXN], d[MAXN], fa[MAXN];
int l[MAXN], r[MAXN], ls[MAXN], rs[MAXN], cnt = 0;
int head[MAXN], cur[MAXN], to[MAXN], next[MAXN], cap[MAXN], tot = 0;
inline void addEdge(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
std::vector<int> V[MAXN];
void build(int &x, int l, int r) {
    x = ++cnt;
    scanf("%d", &t[x]);
    ::l[x] = l;
    ::r[x] = r;
    V[l].push_back(x);
    if (l != r) {
        int mid;
        scanf("%d", &mid);
        build(ls[x], l, mid);
        build(rs[x], mid + 1, r);
        fa[ls[x]] = fa[rs[x]] = x;
        s[x] = s[ls[x]] | s[rs[x]];
        if (!t[x] && s[x]) puts("OwO"), exit(0);
        addEdge(x, ls[x], INF);
    }
    if (s[x] | t[x]) addEdge(x, x + m, INF);
    if (t[x] && !s[x]) {
        addEdge(__s, x, INF);
        addEdge(x + m, __t, INF);
        d[x]--;
        d[x + m]++;
    }
    s[x] |= t[x];
}
int level[MAXN];
std::queue<int> Q;
inline bool BFS() {
    memset(level, 0, sizeof(level));
    memcpy(cur, head, sizeof(cur));
    Q.push(_s);
    level[_s] = 1;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (!level[to[i]] && cap[i])
                level[to[i]] = level[x] + 1, Q.push(to[i]);
        }
    }
    return level[_t];
}
inline int DFS(int x, int flow) {
    if (x == _t || !flow) return flow;
    int ret = 0, t;
    for (int &i = cur[x]; ~i; i = next[i]) {
        if (level[to[i]] == level[x] + 1 && cap[i] && (t = DFS(to[i], std::min(cap[i], flow)))) {
            flow -= t;
            ret += t;
            cap[i] -= t;
            cap[i ^ 1] += t;
            if (!flow) return ret;
        }
    }
    return ret;
}
inline int Dinic() {
    int ret = 0;
    while (BFS()) ret += DFS(_s, INF);
    return ret;
}
int root;
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    m = (n << 1) - 1;
    build(root, 1, n);
    // puts("SBSB!!");
    for (int i = 1; i <= cnt; i++) {
        int p = r[i] + 1;
        for (int j = 0; j < (int)V[p].size(); j++) {
            if (V[p][j] != rs[fa[i]]) {
                addEdge(i + m, V[p][j], INF);
                break;
            }
        }
    }
    for (int i = 1; i <= cnt << 1; i++) {
        if (d[i] > 0) addEdge(_s, i, d[i]);
        if (d[i] < 0) addEdge(i, _t, -d[i]);
    }
    Dinic();
    addEdge(__t, __s, INF);
    Dinic();
    printf("%d\n", cap[tot - 1]);
    return 0;
}