#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int a, b, c, ans = 0;
int main() {
    scanf("%d%d%d", &a, &b, &c);
    if (a < b) std::swap(a, b);
    if (b < c) std::swap(b, c);
    if (a < b) std::swap(a, b);
    if (b < c) std::swap(b, c);
    while (b < a) b++, c++, ans++;
    while (c < a) c += 2, ans++;
    if (c > a) a++, b++, ans++;
    printf("%d\n", ans);
    return 0;
}