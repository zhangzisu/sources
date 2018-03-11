#include <iostream>
int n, a, b;
int main() {
    std::cin >> n >> a >> b;
    register int l = 1, r = a + b, mid, ans = -1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if ((a / mid) + (b / mid) >= n && (a / mid) && (b / mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    std::cout << ans << std::endl;
    return 0;
}