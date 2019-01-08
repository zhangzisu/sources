#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include<cassert>
#define MAXN 200010
#define MAXM 20000010
typedef long long lnt;
int n, m, p1, p2, k[MAXN], tl[MAXN], tr[MAXN];
int stk[MAXN], top = 0;
struct opt {
    int l, r, val;
    inline opt(int l, int r, int val) : l(l), r(r), val(val) {}
};
std::vector<opt> d[MAXN];
int L[MAXM], R[MAXM], root[MAXN], cnt = 0;
lnt sum[MAXM], tag[MAXM];
inline void copy(int &n, int N) {
    n = ++cnt;
    L[n] = L[N], R[n] = R[N];
    sum[n] = sum[N], tag[n] = tag[N];
}
void add(int &n, int N, int l, int r, int _l, int _r, int v) {
    copy(n, N);
    if (l == _l && r == _r) {
        tag[n] += v;
        return;
    }
    sum[n] += 1LL * (_r - _l + 1) * v;
    int mid = (l + r) >> 1;
    if (_r <= mid) {
        add(L[n], L[N], l, mid, _l, _r, v);
    } else if (_l > mid) {
        add(R[n], R[N], mid + 1, r, _l, _r, v);
    } else {
        add(L[n], L[N], l, mid, _l, mid, v);
        add(R[n], R[N], mid + 1, r, mid + 1, _r, v);
    }
}
lnt query(int n, int N, int l, int r, int _l, int _r) {
    lnt now = 1LL * (tag[n] - tag[N]) * (_r - _l + 1);
    if (l == _l && r == _r) {
        return now + sum[n] - sum[N];
    }
    int mid = (l + r) >> 1;
    if (_r <= mid) return now + query(L[n], L[N], l, mid, _l, _r);
    if (_l > mid) return now + query(R[n], R[N], mid + 1, r, _l, _r);
    return now + query(L[n], L[N], l, mid, _l, mid) + query(R[n], R[N], mid + 1, r, mid + 1, _r);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &p1, &p2);
    for (int i = 1; i <= n; i++) scanf("%d", &k[i]);
    stk[top = 0] = 0;
    for (int i = 1; i <= n; i++) {
        while (top && k[stk[top]] < k[i]) top--;
        tl[i] = stk[top];
        stk[++top] = i;
    }
    stk[top = 0] = n + 1;
    for (int i = n; i >= 1; i--) {
        while (top && k[stk[top]] < k[i]) top--;
        tr[i] = stk[top];
        stk[++top] = i;
    }
    // for (int i = 1; i <= n; i++) printf("DBG : %d => [%d - %d]\n", i, tl[i], tr[i]);
    for (int i = 1; i <= n; i++) {
        if (i ^ n) d[i].push_back(opt(i + 1, i + 1, p1));
        if (tl[i] && tr[i] <= n) d[tl[i]].push_back(opt(tr[i], tr[i], p1));
        if (tl[i] && i < tr[i] - 1) d[tl[i]].push_back(opt(i + 1, tr[i] - 1, p2));
        if (i > tl[i] + 1 && tr[i] <= n) d[tr[i]].push_back(opt(tl[i] + 1, i - 1, p2));
    }
    int opts = 0;
    for (int x = 1; x <= n; x++) {
        root[x] = root[x - 1];
        for (auto p : d[x]) {
            // printf("ADD %d : %d - %d : %d\n", x, d.l, d.r, d.val);
            add(root[x], root[x], 1, n, p.l, p.r, p.val);
            opts++;
        }
        if(cnt >= MAXM){
            printf("opts : %d,  %d => %d\n", opts, x, cnt);
            return 0;
        }
    }
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", query(root[r], root[l - 1], 1, n, l, r));
    }
    return 0;
}