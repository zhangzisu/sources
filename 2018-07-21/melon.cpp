#include <cstdio>
#define MOD 1000000007
int main() {
    for (int n; scanf("%d",&n) == 1;) {
        printf("%lld\n", ((1LL * n * n % MOD * n % MOD + 5LL * n % MOD) * 166666668LL % MOD + 1) % MOD);
    }
}