#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 1000000007
void printb(int x, int len) {
    for (int i = len; i; i--) putchar('0' ^ ((x >> (i - 1)) & 1));
    putchar(10);
}
inline int fuck(int x, int p) {
    register int ret = 1;
    while (p) {
        if (p & 1) ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
int subInt(int x, int l, int len) {
    return (x >> l) & ((1 << len) - 1);
}
int gen(int len) {
    int ret = 0;
    for (int i = 0; i < (1 << len); i++) {
        for (int j = 2; j < len; j++) {
            if (len % j) continue;
            int sample = subInt(i, 0, j);
            int mask = (1 << j) - 1;
            for (int k = j; k < len; k += j) {
                int ex = subInt(i, k, j);
                if (ex != sample && (ex ^ mask) != sample) goto ok;
            }
            goto fail;
        ok:;
        }
        ret++;
    fail:;
    }
    printf("GEN %d = %d\n", len, ret);
    return ret;
}
int n, ans = 0;
int main() {
    scanf("%d", &n);
    int ans=0;
    for(int i=2;i<=n;i++)ans+=gen(i);
    printf("%d\n", ans);
    return 0;
}