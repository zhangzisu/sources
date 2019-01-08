#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
unsigned long long a[100010], ans, tmp;
int n, k;
inline int _1() {
    for (int i = 1; i <= n; i++) ans |= a[i];
    printf("%llu", ans >> 1);
    if (ans & 1) printf(".5");
    return puts(""), 0;
}
inline int _2() {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            bool flag = true;
            for (int k = 1; k <= n; k++)
                if ((a[k] >> i) & 1) {
                    flag = false;
                    break;
                }
            if (flag) continue;
            flag = true;
            for (int k = 1; k <= n; k++)
                if ((a[k] >> j) & 1) {
                    flag = false;
                    break;
                }
            if (flag) continue;
            flag = false;
            for (int k = 1; k <= n; k++)
                if ((a[k] >> i) ^ (a[k] >> j)) {
                    flag = true;
                    break;
                }
            if (i + j - 1 - flag < 0) {
                tmp++;
            } else {
                ans += 1ULL << (i + j - 1 - flag);
            }
        }
    }
    ans += tmp >> 1;
    tmp &= 1;
    printf("%llu", ans);
    if (tmp) printf(".5");
    return puts(""), 0;
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%llu", &a[i]);
    if (k == 1) return _1();
    if (k == 2) return _2();
    return 0;
}