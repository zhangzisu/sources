#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>
long long n, H;

int main() {
    scanf("%I64d%I64d", &n, &H);
    long long ans = sqrt(n * 2) + 1;
    while (ans * (ans - 1) / 2 >= n) ans--;
    if (ans <= H) return printf("%I64d\n", ans), 0;
    long long l = H, r = 2e9;
    ans = 0x3F3F3F3F3F3F3F3FLL;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        long long dist = (mid - H + 1);
        long long countL = (H + mid) * dist / 2;
        long long countR = (1 + mid) * (mid) / 2;
        long long sum = countL + countR - mid;
        if (sum > n) {
            r = mid - 1;
            continue;
        }
        long long rest = n - sum;
        long long rr = rest % mid;
        rest = rest / mid;
        if (rr) rest++;
        ans = std::min(ans, dist + mid - 1 + rest);
        l = mid + 1;
    }
    printf("%I64d\n", ans);
    return 0;
}