#include<iostream>
#include<algorithm>
#include<deque>
#define MAXN 300010
long long n, a, b, c, d, s, l, ans = -1;
struct pa{
    long long time, sum0, sum1, min;
}sb[MAXN];
std::deque<pa> g;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin >> n >> a >> b >> c >> d >> s >> l;
    sb[0] = {0, s, 0};
    for(int i = 1, x;i <= n;i++){
        std::cin >> sb[i].time >> x;
        sb[i].sum0 = sb[i - 1].sum0 + (x ? a : -b);
        sb[i].sum1 = sb[i - 1].sum1 + (x ? c : -d);
    }
    for(int i = n;i >= 1;i--){
        while(g.size() && g.front().time > sb[i].time + l)g.pop_front();
        while(g.size() && g.back().sum1 > sb[i].sum1)g.pop_back();
        g.push_back(sb[i]);
        sb[i].min = g.front().sum1 - sb[i - 1].sum1;
    }
    sb[0].time = -1;
    for(int i = 1;i <= n + 1;i++){
        if(sb[i - 1].sum0 >= 0 && sb[i - 1].sum0 + sb[i].min >= 0){
            ans = sb[i - 1].time + 1; break;
        }else if(sb[i - 1].sum0 < 0)break;
    }
    std::cout << ans << std::endl;
    return 0;
}
// 5 332015144 612394901 328775155 121886841 728906738 127569406
// 10430019 1
// 24712957 0
// 25437690 1
// 40008228 1
// 47909053 1