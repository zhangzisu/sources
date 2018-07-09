#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0, f = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    if (!(ch ^ 45)) ch = gc(), f = 1;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
#define MAXN 100010
int n = $(), res;
int a[MAXN][3];
int main() {
    for (int i = 1; i <= n; i++) {
        a[i][0] = a[i - 1][0];
        a[i][1] = a[i - 1][1];
        a[i][2] = a[i - 1][2];
        a[i][$()]++;
        // printf("Suffix:%d %d %d\n", a[i][0], a[i][1], a[i][2]);
        // printf("Node %d, %d\n", a[i][0] - a[i][1], a[i][0] - a[i][2]);
    }
    for (int i = 0; i <= n; i++)
        for (int j = i; j <= n; j++)
            if ((a[j][0] - a[i][0]) == (a[j][1] - a[i][1]) &&
                (a[j][0] - a[i][0]) == (a[j][2] - a[i][2]))
                res = std::max(res, j - i);
    printf("%d\n", res);
    return 0;
}
