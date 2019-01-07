#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 11
int n, m, a[MAXN][MAXN], b[MAXN][MAXN], stat[MAXN];
std::map<long long, int> D;
inline long long getHashCode(int g) {
    long long ret = 1;
    for (int i = 1; i <= n; i++) ret *= 11, ret += stat[i];
    return ret << g;
}
int DDD(int);
int AAA(int);
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &b[i][j]);
    stat[0] = m;
    printf("%d\n", DDD(1));
    return 0;
}

int DDD(int deep) {
    if (deep > n * m) return 0;
    long long exp = getHashCode(0);
    if (D.count(exp)) return D[exp];
    int ret = 0x80000000;
    for (int i = 1; i <= n; i++) {
        if (!stat[i - 1] && !stat[i]) break;
        if (stat[i - 1] == stat[i]) continue;
        ++stat[i];
        int tmp = a[i][stat[i]] + AAA(deep + 1);
        if (tmp > ret) ret = tmp;
        stat[i]--;
    }
    return D[exp] = ret;
}
int AAA(int deep) {
    if (deep > n * m) return 0;
    long long exp = getHashCode(1);
    if (D.count(exp)) return D[exp];
    int ret = 0x7FFFFFFF;
    for (int i = 1; i <= n; i++) {
        if (!stat[i - 1] && !stat[i]) break;
        if (stat[i - 1] == stat[i]) continue;
        ++stat[i];
        int tmp = -b[i][stat[i]] + DDD(deep + 1);
        if (tmp < ret) ret = tmp;
        stat[i]--;
    }
    return D[exp] = ret;
}