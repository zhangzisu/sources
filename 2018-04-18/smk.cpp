#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 2000000011
const int n = 1000000000;
int x = 1;
int main() {
    for (int i = 1; i <= n; i++) {
        x = 1LL * x * i % MOD;
        if (i % 10000000 == 0) printf(",%d\n", x);
    }
    return 0;
}