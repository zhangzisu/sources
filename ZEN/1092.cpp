#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int n, m, q;
int sum[MAXN << 2], tag[MAXN << 2], a[MAXN];
int op[MAXN], _l[MAXN], _r[MAXN];
inline void pushUp(int n) { sum[n] = sum[n << 1] + sum[n << 1 | 1]; }
inline int pushDown(int n, int l, int r){
    int mid = (l + r) >> 1;
    if(~tag[n]){
        sum[n << 1] = (mid - l + 1) * tag[n];
        tag[n << 1] = tag[n];
        sum[n << 1 | 1] = (r - mid) * tag[n];
        tag[n << 1 | 1] = tag[n];
        tag[n] = -1;
    }
    return mid;
}
void set(int n, int l, int r, int L, int R, int v){
    if(l == L && r == R){
        sum[n] = (r - l + 1) * v;
        tag[n] = v;
        return;
    }
    int mid = pushDown(n, l, r);
    if(R <= mid)set(n << 1, l, mid, L, R, v);
    else if(L > mid)set(n << 1 | 1, mid + 1, r, L, R, v);
    else set(n << 1, l, mid, L, mid, v), set(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    pushUp(n);
}
int get(int n, int l, int r, int L, int R){
    if(l == L && r == R)return sum[n];
    int mid = pushDown(n, l, r);
    if(R <= mid)return get(n << 1, l, mid, L, R);
    if(L > mid)return get(n << 1 | 1, mid + 1, r, L, R);
    return get(n << 1, l, mid, L, mid) + get(n << 1 | 1, mid + 1, r, mid + 1, R);
}
inline bool judge(int mid){
    memset(sum, 0, sizeof(sum));
    memset(tag, 0, sizeof(tag));
    for(int i = 1;i <= n;i++)set(1, 1, n, i, i, a[i] >= mid);
    // for(int i = 1;i <= n;i++)printf("%d ", get(1, 1, n, i, i));puts("");
    for(int i = 1;i <= m;i++){
        int x = get(1, 1, n, _l[i], _r[i]);
        set(1, 1, n, _l[i], _r[i], 0);
        if(x){
            if(op[i])set(1, 1, n, _l[i], _l[i] + x - 1, 1);
            else set(1, 1, n, _r[i] - x + 1, _r[i], 1);
        }
    }
    return get(1, 1, n, q, q);
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
    for(int i = 1;i <= m;i++)scanf("%d%d%d", &op[i], &_l[i], &_r[i]);
    scanf("%d", &q);
    int l = 1, r = n, ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(judge(mid))ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}