#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
#define MOD 998244353
char A[MAXN], B[MAXN];
int n, k;
int main() {
    gets(A + 1);
    gets(B + 1);
    n = strlen(A + 1);
    for (int i = 1; i <= n; i++) k += (A[i] == '1');
    int frac = 1;
    for (int i = 1; i <= k; i++) frac = 1LL * frac * i % MOD;
    frac = 1LL * frac * frac % MOD;
    printf("%d\n", frac);
    return 0;
}