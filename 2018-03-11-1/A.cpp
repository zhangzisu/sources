#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<vector>
#define MAXN 50010

int n, m, k, q, l, r, v;
long long sum[MAXN];
std::vector<std::pair<int, int>> V;

int main() {
    scanf("%d%d%d%d", &m, &n, &k, &q);
    for(int i = 2, t;k != 1;i++){
        if(k % i)continue;
        t = 0;
        while(!(k % i))t++, k /= i;
        V.push_back({i, t});
    }
    assert(m == 1);
    for(int i = 2, x;i <= n;i++){
        scanf("%d", &x);
        sum[i] = sum[i - 1] + x;
    }
    while(q--){
        scanf("%d", &l);
        if(l == 1){
            scanf("%*d%d%*d%d%d", &l, &r, &v);
            //
        }else{
            //
        }
    }
}