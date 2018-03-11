#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<cstring>
#include<map>
#define MAXN 500010
#define MOD 18446744073709551533ULL
#define BASE 3
int n, m, q, c[MAXN];
std::string ss[MAXN], s;
std::map<unsigned long long, int> M;
int val[MAXN], w[MAXN], cnt[MAXN];
inline bool startWith(const std::string &a, const std::string &b){
    if(b.length() > a.length())return 0;
    for(int i = 0;i < (int)b.length();i++)if(a[i] != b[i])return 0;
    return 1;
}
long long ans;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m >> q;
    for(int i = 1;i <= n;i++){
        std::cin >> ss[i];
    }
    for(int i = 1;i <= n;i++){
        std::cin >> c[i];
    }
    for(int i = 1;i <= m;i++)
        std::cin >> val[i];
    for(int i = 1;i <= n;i++)
        std::cin >> w[i];

    if(m == 1){
        for(int i = 1;i <= n;i++){
            unsigned long long hash = 0;
            for(int j = 0;j < (int)ss[i].length();j++){
                hash = hash * BASE + (ss[i][j] ^ 'a') % MOD;
                M[hash]++;
            }
        }
        while(q--){
            int d;
            std::cin >> d;
            if(d == 1){
                std::cin >> s;
                unsigned long long hash = 0;
                for(int j = 0;j < (int)s.length();j++)hash = hash * BASE + (s[j] ^ 'a') % MOD;
                int cnt = M.count(hash) ? M[hash] : 0;
                printf("%lld\n", 1LL * cnt * val[1]);
            }else{
                std::cin >> d >> d;
            }
        }
        return 0;
    }else{
        while(q--){
            int d, dd, ddd;
            std::cin >> d;
            if(d == 1){
                std::cin >> s;
                memset(cnt, 0, sizeof(cnt));
                for(int i = 1;i <= n;i++){
                    if(startWith(ss[i], s))cnt[c[i]]++;
                }
                ans = 0;
                for(int i = 1;i <= m;i++)ans += 1LL * val[i] * w[cnt[i]];
                std::cout << ans << std::endl;
            }else{
                std::cin >> dd >> ddd;
                c[dd] = ddd;
            }
        }
    }
    return 0;
}