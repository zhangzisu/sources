#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int n, q, a[MAXN];
int min[MAXN], max[MAXN], sum[MAXN], tag[MAXN];
inline void pushUp(int n){
    min[n] = std::min(min[n << 1], min[n << 1 | 1]);
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
inline void build(int n, int l, int r){
    if(l == r)return void(min[n] = max[n] = sum[n] = a[l]);
    int mid = (l + r) >> 1;
    build(n << 1, l, mid); build(n << 1 | 1, mid + 1, r);
    pushUp(n);
}
inline void add(int n, int l, int r, int L, int R, int v){
    if(l == L && r == R){
        min[n] += v; max[n] += v; sum[n] += (r - l + 1) * v; tag[n] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid)add(n << 1, l, mid, L, R, v);
    else if(L > mid)add(n << 1 | 1, mid + 1, r, L, R, v);
    else add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    pushUp(n);
}
inline void div(int n, int l, int r, int L, int R, int v){
    //
}
int main(){
    scanf("%d%d", &n, &q);
    for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
    return 0;
}