#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>
long long n, k, l, m;
long long a[100010];
int main() {
    scanf("%I64d%I64d%I64d", &n, &k, &l);
    m = n * k;
    for (long long i = 1; i <= m; i++) scanf("%I64d", &a[i]);
    std::sort(a + 1, a + m + 1);
    long long x = 0;
    long long max = a[1] + l;
    for (long long i = 1; i <= m; i++) {
        if (a[i] > max) break;
        x = i;
    }
    long long len = x;
    if(len < n)return puts("0"), 0;
    long long rest = m - len, ans = 0;
    for(long long i = x;i;i--){
        rest++;
        if(rest >= k){
            rest -= k;
            ans += a[i];
        }
    }
    printf("%I64d\n", ans);
    return 0;
}