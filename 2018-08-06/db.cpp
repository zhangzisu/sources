#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, a[10], cnt[150];
inline void calc() {
    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) tot++;
        }
    }
    cnt[tot]++;
    if (tot <= 2) {
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("TOT: %d\n", tot);
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) a[i] = i;
    do {
        calc();
    } while (std::next_permutation(a, a + n));
    int all = 0, frc = 1, tot = 0;
    for (int i = 1; i <= n; i++) frc *= i;
    for (int i = 0; all < frc; i++) {
        printf("cnt[%d] = %d\n", i, cnt[i]);
        all += cnt[i];
        tot += cnt[i] * i;
    }
    printf("RESULT: %f\n", 1. * tot / frc);
    return 0;
}