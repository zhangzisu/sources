#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
int _0;
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() {
    fwrite(_2, 1, _4 - _2, stdout);
    exit(0);
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline void pi(int x) {
    static int _5[32];
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#define MAXN 100010
#define MAXM 5000010
#define SQRT 320
#include <vector>
int n, m, k, a[MAXN];
int root[MAXN], sum[MAXM], L[MAXM], R[MAXM], cnt;
std::vector<int> pos[SQRT][SQRT];
inline int insert(int n, int l, int r, int p) {
    int cur = ++cnt;
    sum[cur] = sum[n] + 1, L[cur] = L[n], R[cur] = R[n];
    if (l == r) return cur;
    int mid = (l + r) >> 1;
    if (p <= mid) {
        L[cur] = insert(L[n], l, mid, p);
    } else {
        R[cur] = insert(R[n], mid + 1, r, p);
    }
    return cur;
}
inline int query(int n, int m, int l, int r, int _l, int _r) {
    if (!(sum[n] - sum[m])) return 0;
    int mid = (l + r) >> 1, t;
    if (l == r) return l;
    if (_r <= mid) return query(L[n], L[m], l, mid, _l, _r);
    if (_l > mid) return query(R[n], R[m], mid + 1, r, _l, _r);
    return (t = query(R[n], R[m], mid + 1, r, mid + 1, _r)) ? t : query(L[n], L[m], l, mid, _l, mid);
}
int main() {
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
    n = $(), m = $();
    for (int i = 1; i <= n; i++) k = std::max(k, a[i] = $());
    for (int i = 1; i < SQRT; i++) {
        for (int j = 1; j <= n; j++) {
            pos[i][a[j] % i].push_back(j);
        }
    }
    for (int i = 1; i <= n; i++) root[i] = insert(root[i - 1], 1, k, a[i]);
    for (int l, r, t, ans; m; m--) {
        l = $(), r = $(), t = $();
        ans = 0;
        if (t >= SQRT) {
            for (int L = 0, R = t - 1; L <= k;) {
                int max = query(root[r], root[l - 1], 1, k, std::max(1, L), std::min(R, k));
                ans = std::max(ans, max - L);
                L += t, R += t;
            }
        } else {
            for (int i = t - 1; i >= 0; i--) {
                std::vector<int>::iterator it = std::lower_bound(pos[t][i].begin(), pos[t][i].end(), l);
                if (it == pos[t][i].end() || *it > r) continue;
                ans = i;
                break;
            }
        }
        pi(ans);
        pc(10);
    }
    rt();
}