#include <cstdio>
#include <cstdlib>
#include <set>
using std::set;
#define MAXN 1000010
#define MOD 1061109559
#define BASE 37
int n, po[MAXN], A[MAXN], ans[MAXN];
inline int a(int x, int y) { return ((A[y] - 1LL * A[x - 1] * po[y - x + 1] % MOD) + MOD) % MOD; }
char buf[MAXN];
int main() {
    scanf("%d%s", &n, buf + 1);
    for (int i = po[0] = 1; i <= n; i++) po[i] = 1LL * po[i - 1] * BASE % MOD;
    for (int i = 1; i <= n; i++) A[i] = (1LL * A[i - 1] * BASE + buf[i] - 'a') % MOD;
    for (int i = (n + 1) >> 1, now = -1; i; i--) {
        now += 2;
        if (i * 2 > n) now = -1;
        while (~now && a(i, i + now - 1) != a(n - i - now + 2, n - i + 1)) now -= 2;
        ans[i] = now;
    }
    for (int i = 1; i <= (n + 1) >> 1; i++) printf("%d%c", ans[i], " \n"[i == (n + 1) >> 1]);
    return 0;
}