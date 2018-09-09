#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
inline int getint()
{
    int r = 0,s = 1;char c = getchar();for(;!isdigit(c);c = getchar()) if(c == '-') s = 0;
    for(;isdigit(c);c = getchar()) r = (((r << 2) + r) << 1) + (c ^ '0');return s ? r : -r;
}
const int N = 100010;
int n,l,a[N],b[N],nc,c[N];
struct SegmentTree
{
    int mn[N << 3];
    inline void init(){memset(mn,0x3f,sizeof(mn));}
    inline void modify(int k,int l,int r,int p,int v)
    {
        if(l == r) {mn[k] = std::min(mn[k],v);return;}
        int mid = (l + r) >> 1;
        if(p <= mid) modify(k << 1,l,mid,p,v);
        else modify(k << 1 | 1,mid + 1,r,p,v);
        mn[k] = std::min(mn[k << 1],mn[k << 1 | 1]);
    }
    inline int query(int k,int l,int r,int L,int R)
    {
        if(l == L && r == R) return mn[k];
        int mid = (l + r) >> 1;
        if(R <= mid) return query(k << 1,l,mid,L,R);
        if(L > mid) return query(k << 1 | 1,mid + 1,r,L,R);
        return std::min(query(k << 1,l,mid,L,mid),query(k << 1 | 1,mid + 1,r,mid + 1,R));
    }
}SGT;
inline int judge(int x)
{
    for(int i = 1;i <= n;i++) c[i] = (a[i] >= x) ? 1 : -1;
    for(int i = 1;i <= n;i++) c[i] += c[i - 1];
    // puts("----------");
    // printf("m %d\n",x);
    // for(int i = 1;i <= n;i++) printf("c %d %d\n",i,c[i]);
    SGT.init();
    // for(int i = 1;i <= n;i++) mn[c[i] + n + 1] = std::min(mn[c[i] + n + 1],i);
    SGT.modify(1,1,n + n + 1,n + 1,0);
    for(int i = 1;i <= n;i++)
    {
        SGT.modify(1,1,n + n + 1,c[i] + n + 1,i);
    }
    for(int i = l;i <= n;i++) if((i - SGT.query(1,1,n + n + 1,1,c[i] + n + 1 - 1)) >= l) 
    {
        // puts("Y");
        return 1;
    }
    // puts("N");
    return 0;
}
int main()
{
    n = getint(),l = getint();
    for(int i = 1;i <= n;i++) b[i] = a[i] = getint();
    std::sort(b + 1,b + n + 1);
    nc = std::unique(b + 1,b + n + 1) - b - 1;
    for(int i = 1;i <= n;i++) a[i] = std::lower_bound(b + 1,b + nc + 1,a[i]) - b;
    int l = 1,r = nc,mid,ans = 1;
    while(l <= r)
    {
        mid = (l + r) >> 1;
        if(judge(mid)) l = mid + 1,ans = mid;
        else r = mid - 1;
    }
    printf("%d\n",b[ans]);
    return 0;
}