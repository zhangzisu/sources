#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
const int MAXD = 400;
const int MAXN = 400;
int n, m, p[MAXN];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
std::bitset<MAXD> base[MAXD], val[MAXN];
inline void insert(std::bitset<MAXD> x) {
    for (int i = m - 1; ~i; i--) {
        if (x[i]) {
            if (base[i].none()) {
                base[i] = x;
                return;
            } else {
                x ^= base[i];
            }
        }
    }
}
bool zero = true;
int main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = m - 1, x; ~j; j--) {
            scanf("%1d", &x);
            if (x) val[i].set(j);
        }
        insert(val[i]);
        zero &= val[i].none();
    }
    p[0] = 1;
    for (int i = 1; i < m; i++) p[i] = (p[i - 1] << 1) % MOD;
    if (zero) return puts("0"), 0;
    int ret = 0, cnt = 0;
    for (int d = 0; d < m; d++) cnt += !base[d].none();
    for (int d = 0; d < m; d++) {
        for (int i = 0; i < m; i++) {
            if (base[i][d]) {
                up(ret, 1LL * p[d] * p[cnt - 1] % MOD);
                break;
            }
        }
    }
    printf("%d\n", ret);
    return 0;
}