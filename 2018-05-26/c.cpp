#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#define MAXN 5010
#define int long long
const int INF = (~0ull) >> 1;
int n, k, q, a[MAXN], b[MAXN], ans = INF;
std::vector<std::pair<int, int>> V;

inline int calc(int l, int r, int max){
    int len = r - l + 1;
    int mc = len - k + 1;
    int ret = 0;
    for(int i = l;i <= r;i++)if(a[i] <= max)ret++;
    return std::max(std::min(ret, mc), 0LL);
}

inline bool judge(int min, int max){
    int L = -1, R = -1;
    V.clear();
    for(int i = 1;i <= n;i++){
        if(a[i] < min){
            if(~L)V.push_back({L, R});
            L = R = -1;
        }else{
            if(!~L)L = i;
            R = i;
        }
    }
    if(~L)V.push_back({L, R});
    int ret = 0;
    for(auto x : V){
        assert(x.first <= x.second);
        ret += calc(x.first, x.second, max);
    }
    return ret >= q;
}
signed main(){
    scanf("%lld%lld%lld", &n, &k, &q);
    for(int i = 1;i <= n;i++)scanf("%lld", &a[i]);
    memcpy(b, a, sizeof(a));
    std::sort(b + 1, b + n + 1);
    for(int i = 1;i <= n;i++){
        if(i + q - 1 > n)break;
        int l = i + q - 1, r = n, tmp = INF;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(judge(b[i], b[mid])){
                tmp = b[mid] - b[i];
                r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        ans = std::min(ans, tmp);
    }
    printf("%lld\n", ans);
    return 0;
}