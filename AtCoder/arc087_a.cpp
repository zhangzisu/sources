#include <algorithm>
#include <iostream>
int n, m, a[100010], b[100010], c[100010], ans;
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        if (a[i] != c[m])
            c[++m] = a[i], b[m] = 1;
        else
            b[m]++;
    for (int i = 1; i <= m; i++)
        if (b[i] >= c[i])
            ans += b[i] - c[i];
        else
            ans += b[i];
    std::cout << ans << std::endl;
    return 0;
}