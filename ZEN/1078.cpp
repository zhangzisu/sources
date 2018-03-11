#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>

#define MAXN 200010
#define MOD 1000000007
int n, m, a[MAXN];
inline int fuck(int n, int p){
    int ret = 1;
    while(p){
        if(p & 1)ret = 1LL * ret * n % MOD;
        n = 1LL * n * n % MOD;
        p >>= 1;
    }
    return ret;
}
inline int lowbit(int x){ return x & -x; }
inline void add(int &x, int y) {x += y; x -= (x >= MOD ? MOD : 0); }
std::pair<int, int> BTA[MAXN], BTB[MAXN];
inline void dn(int x, std::pair<int, int> v){
    for(;x <= n;x += lowbit(x)){
        if(BTA[x].first == v.first)add(BTA[x].second, v.second);
        else if(BTA[x].first < v.first)BTA[x] = v;
    }
}
inline std::pair<int, int> dnq(int x){
    std::pair<int, int> ret;
    for(;x;x -= lowbit(x)){
        if(BTA[x].first == ret.first)add(ret.second, BTA[x].second);
        else if(BTA[x].first > ret.first)ret = BTA[x];
    }
    return ret;
}
inline void up(int x, std::pair<int, int> v){
    for(;x;x -= lowbit(x)){
        if(BTB[x].first == v.first)add(BTB[x].second, v.second);
        else if(BTB[x].first < v.first)BTB[x] = v;
    }
}
inline std::pair<int, int> upq(int x){
    std::pair<int, int> ret;
    for(;x <= n;x += lowbit(x)){
        if(BTB[x].first == ret.first)add(ret.second, BTB[x].second);
        else if(BTB[x].first > ret.first) ret = BTB[x];
    }
    return ret;
}

std::pair<int, int> f[MAXN], g[MAXN], tmp;
int ans = 0, res = 0;
std::map<int, int> M;

int main(){
    scanf("%d", &n);
    for(int i = 1;i <= n;i++)scanf("%d", &a[i]), M[a[i]] = 1;
    for(auto &i : M)i.second = ++m;
    for(int i = n;i >= 1;i--){
        a[i] = M[a[i]];
        tmp = upq(a[i] + 1); f[i] = {tmp.first + 1, std::max(tmp.second, 1)}; up(a[i], f[i]);
        tmp = dnq(a[i] - 1); g[i] = {tmp.first + 1, std::max(tmp.second, 1)}; dn(a[i], g[i]);
    }
    for(int i = 1;i <= n;i++)ans = std::max(ans, f[i].first + g[i].first - 1);
    printf("%d ", ans);
    for(int i = 1;i <= n;i++){
        if(f[i].first + g[i].first - 1 == ans){
            (res += 1LL * f[i].second * g[i].second % MOD * fuck(2, n - ans) % MOD) %= MOD;
        }
    }
    printf("%d\n", res);
    return 0;
}