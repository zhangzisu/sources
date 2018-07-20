#include <algorithm>
#include <cstdio>
#include <cstring>
#define fo(i, a, b) for (int i = a; i <= b; i++)
#define fd(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef double db;
typedef long long ll;
const int N = 3 * 1e5 + 5;
struct note {
    int d, t;
} a[N];
struct node {
    int v;
    ll c;
} t[N], T[N], d[N], D[N];
int n, atk, q[N];
ll c[N], sum, ans;
bool cmp(note x, note y) {
    return (db)x.t / x.d < (db)y.t / y.d;
}
db calc(int x, int y) {
    if (t[x].v == t[y].v) {
        if (t[y].c <= t[x].c)
            return 0;
        else
            return 1e18;
    }
    return (db)(t[y].c - t[x].c) / (t[y].v - t[x].v);
}
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    solve(l, mid);
    solve(mid + 1, r);
    int le = 1, ri = 0;
    fo(i, l, mid) {
        while (le < ri && calc(q[ri - 1], q[ri]) < calc(q[ri], i)) ri--;
        q[++ri] = i;
    }
    fo(i, mid + 1, r) {
        while (le < ri && calc(q[le], q[le + 1]) >= d[i].v) le++;
        ans = min(ans, sum - d[i].c - t[q[le]].c + t[q[le]].v * d[i].v);
    }
}
int main() {
    scanf("%d%d", &n, &atk);
    fo(i, 1, n) scanf("%d%d", &a[i].d, &a[i].t), a[i].t = a[i].t / atk + (a[i].t % atk > 0);
    sort(a + 1, a + n + 1, cmp);
    ll res = 0;
    fo(i, 1, n) {
        res += (ll)a[i].t;
        c[i] += (ll)(res - 1) * a[i].d;
    }
    fo(i, 1, n) sum += c[i];
    ans = sum;
    res = 0;
    fd(i, n, 1) {
        c[i] += (ll)res * a[i].t;
        res += (ll)a[i].d;
    }
    fo(i, 1, n) d[i].v = a[i].d, t[i].v = a[i].t, d[i].c = t[i].c = c[i];
    solve(1, n);
    printf("%lld\n", ans);
}