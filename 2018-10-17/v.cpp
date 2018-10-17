#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#define MAXN 30
int n, k, init, cnt;
char buf[50];
typedef long long lnt;
std::unordered_map<lnt, double> S;
inline int remove(int x, int p) {
    return (x >> (p + 1) << p) | (x & ((1 << p) - 1));
}
double dfs(int stat, int now) {
    if (now >= k) return 0;
    if (S.count((lnt)now << 32 | stat)) return S[(lnt)now << 32 | stat];
    double res = 0;
    for (int i = 0; i < n - now; i++) {
        res += std::max(dfs(remove(stat, i), now + 1) + ((stat >> i) & 1), dfs(remove(stat, n - now - i - 1), now + 1) + ((stat >> (n - now - i - 1)) & 1));
    }
    res /= n - now;
    return S[(lnt)now << 32 | stat] = res;
}
int main() {
    scanf("%d%d%s", &n, &k, buf);
    for (int i = 0; i < n; i++) init |= (buf[i] == 'W') << i;
    printf("%f\n", dfs(init, 0));
    fprintf(stderr, "%d\n", (int)S.size());
    return 0;
}