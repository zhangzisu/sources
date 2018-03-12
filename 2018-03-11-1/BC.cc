#include <bits/stdc++.h>

using namespace std;

#define LL long long
#define N 520000
#define gb(x) ((x) / 1800)
#define INF 0x3f3f3f3f

int n, m, p, op, x, y, tim, clk, cnt, cnt1, cnt2;
int pos[N], kd[N], val[N], w[N], dfn[N], fst[N], lst[N], c[N][2], sum[N];
LL ans, out[N];
bool vis[N];
vector<int> cg[N];
char s[N];
struct qry {
    int l, r, t, i;
    qry(int l = 0, int r = 0, int t = 0, int i = 0) : l(l), r(r), t(t), i(i) {}
    bool operator<(const qry s) const {
        return gb(l) < gb(s.l) || (gb(l) == gb(s.l) && gb(r) < gb(s.r)) || (gb(l) == gb(s.l) && gb(r) == gb(s.r) && t < s.t);
    }
} q1[N];
struct mdf {
    int x, y;
    mdf(int x = 0, int y = 0) : x(x), y(y) {}
} q2[N];

int getint() {
    char ch;
    int sum = 0;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar())
        ;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + ch - '0';
    return sum;
}

void dfs(int u) {
    fst[u] = INF;
    lst[u] = 0;
    if (vis[u]) dfn[u] = fst[u] = lst[u] = ++tim;
    for (int i = 0, v; i < 2; i++)
        if ((v = c[u][i]) != 0) {
            dfs(v);
            lst[u] = max(lst[u], lst[v]);
            fst[u] = min(fst[u], fst[v]);
        }
}

int main() {
    n = getint();
    m = getint();
    p = getint();
    cnt = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        int xb = 1;
        for (int j = 1; j <= len; j++)
            if (c[xb][s[j] - 'a'])
                xb = c[xb][s[j] - 'a'];
            else
                xb = c[xb][s[j] - 'a'] = ++cnt;
        pos[i] = xb;
        vis[xb] = 1;
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        int j = dfn[pos[i]];
        kd[j] = getint();
        cg[j].push_back(kd[j]);
    }
    for (int i = 1; i <= m; i++) val[i] = getint();
    for (int i = 1; i <= n; i++) w[i] = getint();
    for (int i = 1; i <= p; i++) {
        op = getint();
        if (op == 1) {
            scanf("%s", s + 1);
            int len = strlen(s + 1);
            int xb = 1;
            for (int j = 1; j <= len; j++) xb = c[xb][s[j] - 'a'];
            ++cnt1;
            q1[cnt1] = qry(fst[xb], lst[xb], clk, cnt1);
        }
        if (op == 2) {
            x = getint();
            y = getint();
            x = dfn[pos[x]];
            cg[x].push_back(y);
            q2[++clk] = mdf(x, (int)cg[x].size() - 1);
        }
    }
    sort(q1 + 1, q1 + cnt1 + 1);
    ans = 0;
    for (int i = 1, l = 1, r = 0, t = 0; i <= cnt1; i++) {
        int ll = q1[i].l, rr = q1[i].r, tt = q1[i].t;
        if (ll == 0 || rr == 0) continue;
        // printf("L:%d, R:%d, T:%d, id:%d.\n", ll, rr, tt, q1[i].i);
        while (t < tt) {
            ++t;
            x = q2[t].x;
            y = cg[x][q2[t].y];
            if (x >= l && x <= r) {
                --sum[kd[x]];
                ans += ((LL)w[sum[kd[x]]] - w[sum[kd[x]] + 1]) * val[kd[x]];
                ++sum[y];
                ans += ((LL)w[sum[y]] - w[sum[y] - 1]) * val[y];
            }
            kd[x] = y;
        }
        while (t > tt) {
            x = q2[t].x;
            y = cg[x][q2[t].y - 1];
            if (x >= l && x <= r) {
                --sum[kd[x]];
                ans += ((LL)w[sum[kd[x]]] - w[sum[kd[x]] + 1]) * val[kd[x]];
                ++sum[y];
                ans += ((LL)w[sum[y]] - w[sum[y] - 1]) * val[y];
            }
            kd[x] = y;
            --t;
        }
        while (l > ll) {
            --l;
            ++sum[kd[l]];
            ans += ((LL)w[sum[kd[l]]] - w[sum[kd[l]] - 1]) * val[kd[l]];
        }
        while (r < rr) {
            ++r;
            ++sum[kd[r]];
            ans += ((LL)w[sum[kd[r]]] - w[sum[kd[r]] - 1]) * val[kd[r]];
        }
        while (l < ll) {
            --sum[kd[l]];
            ans += ((LL)w[sum[kd[l]]] - w[sum[kd[l]] + 1]) * val[kd[l]];
            ++l;
        }
        while (r > rr) {
            --sum[kd[r]];
            ans += ((LL)w[sum[kd[r]]] - w[sum[kd[r]] + 1]) * val[kd[r]];
            --r;
        }
        out[q1[i].i] = ans;
    }
    for (int i = 1; i <= cnt1; i++) printf("%lld\n", out[i]);

    return 0;
}