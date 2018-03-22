#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 500010
int n, m;
long long a[MAXN], b[MAXN], k, l, r;
inline bool judge(long long mid){
    memset(b, 0, sizeof(b));
    long long rest = k;
    for(int i = 1;i <= n;i++){
        b[i] = b[i - 1] + b[i] + a[i];
        if(b[i] <= mid){
            long long delta = mid - b[i];
            if(delta > rest)return 0;
            rest -= delta;
            b[i] += delta;
            b[std::min(n, i + m + m) + 1] -= delta;
        }
    }
    return 1;
}
int main(){
    scanf("%d%d%lld", &n, &m, &k);
    for(int i = 1;i <= n;i++){
        long long x;
        scanf("%lld", &x);
        int s = std::max(1, i - m);
        int e = std::min(n, i + m);
        a[s] += x;
        a[e + 1] -= x;
    }
    l = 0; r = 0x7FFFFFFFFFFFFFFFLL;
    long long ans = -1;
    while(l <= r){
        long long mid = (l + r) >> 1;
        if(judge(mid))ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}