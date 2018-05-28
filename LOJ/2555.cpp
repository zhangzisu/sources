#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 100010
#define MAXM 5000010
typedef long long lnt;
const lnt INFLL = 1e18 + 10;
struct $ {
    lnt d, p, l;
    inline friend bool operator<(const $& a, const $& b) {
        return a.d < b.d;
    }
} _[MAXN];
lnt L[MAXM], R[MAXM], cnt = 0;
lnt sumL[MAXM], sumS[MAXM];
std::map<lnt, lnt> M0, M1;
void insert(lnt& n, lnt N, lnt l, lnt r, lnt p, lnt v) {
    n = ++cnt;
    L[n] = L[N], R[n] = R[N], sumL[n] = sumL[N], sumS[n] = sumS[N];
    if (l == r) {
        sumL[n] += v;
        sumS[n] += M1[l] * v;
        return;
    }
    lnt mid = (l + r) >> 1;
    if (p <= mid)
        insert(L[n], L[N], l, mid, p, v);
    else
        insert(R[n], R[N], mid + 1, r, p, v);
    sumL[n] = sumL[L[n]] + sumL[R[n]];
    sumS[n] = sumS[L[n]] + sumS[R[n]];
}
inline lnt getVal(lnt* arr, lnt n, lnt N) {
    return arr[n] - arr[N];
}
lnt query(lnt n, lnt N, lnt l, lnt r, lnt req) {
    if (getVal(sumL, n, N) < req) return INFLL;
    if (l == r) {
        return req * M1[l];
    }
    lnt mid = (l + r) >> 1;
    if (getVal(sumL, L[n], L[N]) >= req) return query(L[n], L[N], l, mid, req);
    return getVal(sumS, L[n], L[N]) + query(R[n], R[N], mid + 1, r, req - getVal(sumL, L[n], L[N]));
}
lnt n, m, root[MAXN], all;
int main() {
    scanf("%lld%lld", &n, &m);
    for (lnt i = 1; i <= n; i++) {
        scanf("%lld%lld%lld", &_[i].d, &_[i].p, &_[i].l);
        M0[_[i].p] = 1;
    }
    for (auto& x : M0) M1[x.second = ++all] = x.first;
    std::sort(_ + 1, _ + n + 1);
    for (lnt i = 1; i <= n; i++) {
        insert(root[i], root[i - 1], 1, all, M0[_[i].p], _[i].l);
    }
    while (m--) {
        lnt l = 1, r = n, ans = -1, g, d;
        scanf("%lld%lld", &g, &d);
        while (l <= r) {
            lnt mid = (l + r) >> 1;
            if (query(root[n], root[mid - 1], 1, all, d) <= g)
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        printf("%lld\n", ans == -1 ? -1 : _[ans].d);
    }
    return 0;
}