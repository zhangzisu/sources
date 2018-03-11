#include <algorithm>
#include <iostream>
int n, k, m, a[200010], b[200010], ans;
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        if (a[i] != a[i - 1])
            b[++m] = 1;
        else
            b[m]++;
    std::sort(b + 1, b + m + 1);
    for (int i = 1; i <= m - k; i++) ans += b[i];
    std::cout << ans << std::endl;
}