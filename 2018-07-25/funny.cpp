#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#define MAXN 51
int n, m, a[MAXN], b[MAXN], c[MAXN], l[MAXN], r[MAXN], u[MAXN], v[MAXN], d[MAXN];
int _data[MAXN][300], *data[MAXN], top[MAXN], stk[MAXN], now, ans = 0;
struct op {
    int x, type, val;
    inline op(int x, int type, int val) : x(x), type(type), val(val) {}
};
std::vector<op> pre[MAXN];
inline void halt() {
    printf("%d\n", ans);
    exit(0);
}
inline bool valid(int deep, int val) {
    for (auto x : pre[deep]) {
        if (x.type) {
            if (stk[x.x] < val + x.val) return 0;
        } else {
            if (stk[x.x] > val + x.val) return 0;
        }
    }
    return 1;
}
int start, suf[MAXN];
const int limit = CLOCKS_PER_SEC * 0.95;
void dfs(int deep) {
    if (deep > n) {
        ans = std::max(ans, now);
        return;
    }
    if (clock() - start > limit) halt();
    if (now + suf[deep] <= ans) return;
    if (valid(deep, top[deep])) {
        stk[deep] = top[deep];
        now += data[deep][top[deep]];
        dfs(deep + 1);
        now -= data[deep][top[deep]];
    }
    int L = top[deep] - 1, R = top[deep] + 1;
    while (L >= l[deep] || R <= r[deep]) {
        if (L < l[deep] || (R <= r[deep] && data[deep][L] < data[deep][R])) {
            if (valid(deep, R)) {
                stk[deep] = R;
                now += data[deep][R];
                dfs(deep + 1);
                now -= data[deep][R];
            }
            R++;
        } else {
            if (valid(deep, L)) {
                stk[deep] = L;
                now += data[deep][L];
                dfs(deep + 1);
                now -= data[deep][L];
            }
            L--;
        }
    }
}
int main() {
    freopen("funny.in", "r", stdin);
    freopen("funny.out", "w", stdout);
    start = clock();
    for (int i = 0; i < MAXN; i++) data[i] = _data[i] + 150;
    memset(_data, 0x80, sizeof(_data));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &l[i], &r[i]);
        top[i] = l[i];
        for (int j = l[i]; j <= r[i]; j++) {
            data[i][j] = a[i] * j * j + b[i] * j + c[i];
            if (data[i][j] > data[i][top[i]]) top[i] = j;
        }
    }
    for (int i = n; i; i--) suf[i] = suf[i + 1] + data[i][top[i]];

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &d[i]);
        bool flag = 0;
        if (u[i] > v[i]) std::swap(u[i], v[i]), d[i] = -d[i], flag = 1;
        pre[v[i]].push_back(op(u[i], flag, d[i]));
    }
    if (!m) {
        printf("%d\n", suf[1]);
        return 0;
    }
    dfs(1);
    printf("%d\n", ans);
    return 0;
}