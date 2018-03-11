#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#define MAXN 200020
#include <map>
std::map<std::pair<int, int>, int> M;
int a[MAXN][3], n = $();
int main() {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        a[i][0] = a[i - 1][0];
        a[i][1] = a[i - 1][1];
        a[i][2] = a[i - 1][2];
        char c = $();
        a[i][c == 'J' ? 0 : (c == 'O' ? 1 : 2)]++;
        M[std::make_pair(a[i][0] - a[i][1], a[i][0] - a[i][2])] = i;
        // printf("Suffix:%d %d %d\n", a[i][0], a[i][1], a[i][2]);
        // printf("Node %d, %d\n", a[i][0] - a[i][1], a[i][0] - a[i][2]);
    }
    for (int i = 0; i <= n; i++) {
        int x1 = a[i][0] - a[i][1];
        int x2 = a[i][0] - a[i][2];
        res = std::max(res, M[std::make_pair(x1, x2)] - i);
    }
    printf("%d\n", res);
    return 0;
}
