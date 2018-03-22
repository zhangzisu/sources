#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
int n, m, d;
int main() {
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int I = (m + i + j) / d;
            int J = (m + i - j) / d;
            printf("%c", "RYGB"[((I & 1) << 1) | (J & 1)]);
        }
        puts("");
    }
    return 0;
}