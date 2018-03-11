#include <algorithm>
#include <iostream>
#define MAXN 60
using std::cin;
using std::cout;
int n, m, a[MAXN], b[MAXN];
inline long long calc(int x){
    long long ans = 0x8000000000000000LL;
    for(int i = 1;i <= n;i++){
        if(i == x)continue;
        for(int j = 1;j <= m;j++)ans = std::max(ans, 1LL * a[i] * b[j]);
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    long long ans = (~0ULL) >> 1;
    for(int i = 1;i <= n;i++)ans = std::min(ans, calc(i));
    printf("%lld\n", ans);
    return 0;
}