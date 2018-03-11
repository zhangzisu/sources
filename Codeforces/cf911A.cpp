#include <iostream>
int n, m, ans, lp, a[100010];
int main() {
    std::cin >> n;
    m = ans = 0x7FFFFFFF;
    for (int i = 1; i <= n; i++) std::cin >> a[i], m = std::min(m, a[i]);
    lp = -0x3F3F3F3F;
    for (int i = 1; i <= n; i++)
        if (a[i] == m) {
            ans = std::min(ans, i - lp);
            lp = i;
        }
    std::cout << ans << std::endl;
    return 0;
}