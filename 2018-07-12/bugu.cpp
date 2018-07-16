#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MOD 1000000007
#define MAXN 210
struct trie {
    int son[20], fail, size;
    inline int &operator[](int index) {
        return son[index];
    }
} ac[MAXN];
int n, m, k;
int root = 1, cnt = 1;
inline void insert(int *x, int len, int val) {
    int p = root;
    for (int i = 1; i <= len; i++) {
        int &y = ac[p][x[i]];
        if (!y) y = ++cnt;
        p = y;
    }
    ac[p].size += val;
}
std::queue<int> Q;
inline void build() {
    for (int i = 0; i < m; i++) ac[0][i] = 1;
    ac[1].fail = 0;
    Q.push(1);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < m; i++) {
            int &y = ac[x][i];
            if (y) {
                ac[y].fail = ac[ac[x].fail][i];
                ac[y].size += ac[ac[ac[x].fail][i]].size;
                Q.push(y);
            } else {
                y = ac[ac[x].fail][i];
            }
        }
    }
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int f[MAXN][MAXN][510], stk[MAXN];
int dfs(int x, int p, int rest, bool flag, bool prefix) {
    if (rest < 0) return 0;
    if (!x) return 1;
    if (!flag && !prefix && ~f[x][p][rest]) return f[x][p][rest];
    int ret = 0, upper = flag ? stk[x] : m - 1;
    for (int i = 0; i <= upper; i++) {
        int next = prefix && i == 0 ? p : ac[p][i];
        up(ret, dfs(x - 1, next, rest - ac[next].size, flag && i == upper, prefix && i == 0));
    }
    if (!flag && !prefix) f[x][p][rest] = ret;
    return ret;
}
int dl[MAXN], ll, dr[MAXN], lr;
int tmp[MAXN], t, val;
int main() {
    freopen("bugu.in", "r", stdin);
    freopen("bugu.out", "w", stdout);
    memset(f, -1, sizeof(f));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = scanf("%d", &ll); i <= ll; i++) scanf("%d", &dl[ll - i + 1]);
    for (int i = scanf("%d", &lr); i <= lr; i++) scanf("%d", &dr[lr - i + 1]);
    dl[1]--;
    for (int i = 1, t = 0; i <= ll; i++) {
        dl[i] -= t;
        t = 0;
        if (dl[i] < 0) dl[i] += m, t += 1;
    }
    while (ll && !dl[ll]) ll--;

    while (n--) {
        for (int i = scanf("%d", &t); i <= t; i++) scanf("%d", &tmp[i]);
        scanf("%d", &val);
        insert(tmp, t, val);
    }
    build();
    memcpy(stk, dl, sizeof(stk));
    int ansL = dfs(ll, root, k, 1, 1);
    memcpy(stk, dr, sizeof(stk));
    int ansR = dfs(lr, root, k, 1, 1);
    printf("%d\n", (ansR - ansL + MOD) % MOD);
    return 0;
}