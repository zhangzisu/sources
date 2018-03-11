#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXS 900010
#define MAXN 300010
struct state {
    int len, link, son[26];
    inline state(int len = 0) {
        this->len = len;
        this->link = 0;
        memset(son, 0, sizeof(son));
    }
    inline state(const state& x, int len = 0) {
        this->len = len;
        this->link = x.link;
        memcpy(son, x.son, sizeof(son));
    }
    inline int& operator[](int index) { return son[index]; }
} sam[MAXS];
int root = 1, cnt = 1, pre = 1;
int n, val[MAXN], head[MAXS], to[MAXS], next[MAXS], max[MAXS], min[MAXS], size[MAXS], tot = 0;
long long ans[MAXN], ret[MAXN];
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
inline void insert(int x, int val) {
    register int p, q, s, c;
    sam[p = ++cnt] = state(sam[q = pre].len + 1);
    min[p] = max[p] = val, size[p] = 1, pre = p;
    for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
    if (!q) return void(sam[p].link = root);
    s = sam[q][x];
    if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
    sam[c = ++cnt] = state(sam[s], sam[q].len + 1);
    for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
    sam[s].link = sam[p].link = c;
}
char s[MAXN];
void dfs(int x) {
    const int p = sam[x].len;
    for (int i = head[x]; ~i; i = next[i]) {
        dfs(to[i]);
        ans[p] += (long long)size[x] * size[to[i]];
        size[x] += size[to[i]];
        if (min[x] != min[0]) ret[p] = std::max(ret[p], (long long)min[x] * min[to[i]]);
        min[x] = std::min(min[x], min[to[i]]);
        if (max[x] != max[0]) ret[p] = std::max(ret[p], (long long)max[x] * max[to[i]]);
        max[x] = std::max(max[x], max[to[i]]);
    }
}
int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    std::reverse(s + 1, s + n + 1);
    std::reverse(val + 1, val + n + 1);
    memset(size, 0, sizeof(size));
    memset(max, 0xC0, sizeof(max));
    memset(min, 0x3F, sizeof(min));
    memset(head, -1, sizeof(head));
    memset(ret, 0x80, sizeof(ret));
    for (int i = 1; i <= n; i++) insert(s[i] - 'a', val[i]);
    for (int i = 2; i <= cnt; i++) $(sam[i].link, i);
    dfs(1);
    for (int i = n; ~i; i--) ans[i] += ans[i + 1], ret[i] = std::max(ret[i], ret[i + 1]);
    for (int i = 0; i < n; i++) printf("%lld %lld\n", ans[i], ans[i] ? ret[i] : 0);
    return 0;
}