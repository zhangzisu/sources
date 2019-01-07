#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 100010
int n, k[MAXN], f[MAXN], d[MAXN];
std::vector<int> next[MAXN];

int main(){
    scanf("%d", &n);
    for(int i = 2;i <= n;i++)scanf("%d", &fa[i]), next[fa[i]].push_back(i);
    //
    return 0;
}