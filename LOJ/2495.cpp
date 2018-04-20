#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int n = $(), m = $(), p = $(), h[MAXN];
int 
int main() {
    for (int i = 1; i <= n; i++) h[i] = h[i + n] = $();
    build(1, 1, 2 * n);
    return 0;
}