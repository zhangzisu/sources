#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 200010
struct point {
    int l, r;
} p[MAXN];

int n, m, ans, last = 0x80000000;

int main() {
    scanf("%d", &n);
    for (int i = 1, x, w; i <= n; i++) {
        scanf("%d%d", &x, &w);
        p[i] = {x - w, x + w};
    }
    std::sort(p + 1, p + n + 1, [](point a, point b){return a.r < b.r;});
    for(int i = 1;i <= n;i++){
        if(p[i].l >= last){
            ans++;
            last = p[i].r;
        }
    }
    printf("%d\n", ans);
    return 0;
}