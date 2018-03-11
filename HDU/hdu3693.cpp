#pragma comment(linker, "/STACK:16777216")
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define MAXN 300010
#define SIGMA 26
struct state {
    int son[SIGMA], fail;
    inline void reset() {
        memset(son, 0, sizeof(son));
        fail = 0;
    }
    inline int &operator[](int index) { return son[index]; }
} acm[MAXN];
int root, cnt;
inline void insert(const char *s) {
    int p = root;
    for (int i = 0; s[i]; i++) {
        const int x = s[i] - 'a';
        if (!acm[p][x]) acm[p][x] = ++cnt;
        p = acm[p][x];
    }
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
std::vector<int> next[MAXN];
int n, w[20010], dfn[MAXN], size[MAXN], tim;
std::vector<std::string> buf;
inline void init() {
    for (int i = 0; i <= cnt; i++) acm[i].reset(), next[i].clear();
    root = cnt = tim = 0;
    buf.clear();
}
void dfs(int x) {
    dfn[x] = ++tim;
    size[x] = 1;
    for (std::vector<int>::iterator it = next[x].begin(); it != next[x].end();
         it++)
        dfs(*it), size[x] += size[*it];
}
int val[MAXN << 2];
void Modify(int n, int l, int r, int L, int R, int val) {
    if (l == L && r == R) return void(::val[n] = std::max(::val[n], val));
    int mid = (l + r) >> 1;
    if (R <= mid) return Modify(n << 1, l, mid, L, R, val);
    if (L > mid) return Modify(n << 1 | 1, mid + 1, r, L, R, val);
    Modify(n << 1, l, mid, L, mid, val);
    Modify(n << 1 | 1, mid + 1, r, mid + 1, R, val);
}
int Query(int n, int l, int r, int p) {
    if (l == r) return val[l];
    int mid = (l + r) >> 1;
    if (p <= mid) return std::max(val[n], Query(n << 1, l, mid, p));
    return std::max(val[n], Query(n << 1 | 1, mid + 1, r, p));
}
inline void slove(int &test_case) {
    scanf("%d", &n);
    std::string str;
    for (int i = 0; i < n; i++) {
        std::cin >> str >> w[i];
        buf.push_back(str);
        insert(buf[i].c_str());
    }
    build();
    for (int i = 1; i <= cnt; i++) next[acm[i].fail].push_back(i);
    dfs(root);
    memset(val, 0, sizeof(val));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        register int pos = root, f = 0;
        for (int j = 0; j < buf[i].size(); j++) {
            pos = acm[pos][buf[i][j] - 'a'];
            f = std::max(f, Query(1, 1, tim, dfn[pos]) + w[i]);
        }
        Modify(1, 1, tim, dfn[pos], dfn[pos] + size[pos] - 1, f);
        ans = std::max(ans, f);
    }
    std::cout << "Case #" << test_case << ": " << ans << std::endl;
}
int main() {
    int _;
    std::cin >> _;
    for (int i = 1; i <= _; i++) init(), slove(i);
    return 0;
}
