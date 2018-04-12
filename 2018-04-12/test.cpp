#include <cstdio>
int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int tmp = 0;
        for (int j = 1; j * j < i; j++) {
            if (i % j) continue;
            tmp += 2;
            if (j / i == j) tmp--;
        }
        if (n <= 100) printf("IN:%3d | OUT:%3d | ALL:%3d\n", tmp, n / i - 1, tmp + n / i - 1);
        ans += tmp;
    }
    printf("ALL : %d\n", ans);
}