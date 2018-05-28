#include <bits/stdc++.h>
#define gc getchar()
#define lc cur << 1
#define rc lc | 1
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 400009;
int n, a[N], b[N], jc[N], jc_inv[N], sg[N], *beg[N], cnt, len[N], S;
int ksm(int x, int y, int ret = 1) {
    for (; y; y >>= 1, x = (ll)x * x % mod)
        if (y & 1) ret = (ll)ret * x % mod;
    return ret;
}
int read() {
    int x = 1;
    char ch;
    while (ch = gc, ch < '0' || ch > '9')
        if (ch == '-') x = -1;
    int s = ch - '0';
    while (ch = gc, ch >= '0' && ch <= '9') s = s * 10 + ch - '0';
    return s * x;
}
int lim, w[2][N];
void init(int n) {
    lim = 1;
    while (lim <= n) lim <<= 1;
    int G = ksm(3, (mod - 1) / lim);
    w[0][0] = w[0][lim] = w[1][0] = w[1][lim] = 1;
    for (int i = 1; i < lim; i++) w[0][i] = (ll)w[0][i - 1] * G % mod;
    for (int i = 1; i < lim; i++) w[1][i] = w[0][lim - i];
}
void dft(int *a, int flag) {
    for (int i = 0, j = 0; i < lim; i++) {
        if (i > j) swap(a[i], a[j]);
        for (int l = lim >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for (int i = 2; i <= lim; i <<= 1)
        for (int j = 0; j < lim; j += i)
            for (int k = 0; k<i>> 1; k++) {
                int x = a[j + k], y = (ll)a[j + k + (i >> 1)] * w[flag][lim / i * k] % mod;
                a[j + k + (i >> 1)] = (x - y < 0 ? x - y + mod : x - y);
                a[j + k] = (x + y >= mod ? x + y - mod : x + y);
            }
    if (flag)
        for (int i = 0, t = ksm(lim, mod - 2); i < lim; i++)
            a[i] = (ll)a[i] * t % mod;
}
int A[N], B[N];
void ntt(int *a, int n, int *b, int m) {
    init(n + m);
    for (int i = 0; i <= n; i++) A[i] = a[i];
    for (int i = n + 1; i < lim; i++) A[i] = 0;
    for (int i = 0; i <= m; i++) B[i] = b[i];
    for (int i = m + 1; i < lim; i++) B[i] = 0;
    dft(A, 0), dft(B, 0);
    for (int i = 0; i < lim; i++) A[i] = (ll)A[i] * B[i] % mod;
    dft(A, 1);
    for (int i = 0; i <= n + m; i++) a[i] = A[i];
}
int C(int n, int m) {
    if (n < m) return 0;
    return (ll)jc[n] * jc_inv[m] % mod * jc_inv[n - m] % mod;
}
void solve(int l, int r, int cur) {
    if (l == r) {
        beg[cur] = sg + cnt;
        for (int i = 0; i <= min(a[l], b[l]); i++)
            sg[cnt++] = (ll)C(a[l], i) * C(b[l], i) % mod * jc[i] % mod;
        len[cur] = min(a[l], b[l]);
        return;
    }
    int mid = l + r >> 1;
    solve(l, mid, lc), solve(mid + 1, r, rc);
    ntt(beg[lc], len[lc], beg[rc], len[rc]);
    beg[cur] = beg[lc], len[cur] = len[lc] + len[rc];
}
int main() {
    jc[0] = 1;
    for (int i = 1; i < N; i++) jc[i] = (ll)jc[i - 1] * i % mod;
    jc_inv[N - 1] = ksm(jc[N - 1], mod - 2);
    for (int i = N - 2; ~i; i--) jc_inv[i] = (ll)jc_inv[i + 1] * (i + 1) % mod;
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), b[i] = read(), S += a[i];
    solve(1, n, 1);
    int Ans = 0;
    for (int i = 0; i <= len[1]; i++)
        if (i & 1)
            Ans = (Ans - (ll)sg[i] * jc[S - i] % mod + mod) % mod;
        else
            Ans = (Ans + (ll)sg[i] * jc[S - i] % mod) % mod;
    printf("%d\n", Ans);
    return 0;
}