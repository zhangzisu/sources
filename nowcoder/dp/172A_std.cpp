//Keep pluggin,this is your only outlet.
#include<bits/stdc++.h>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define MM(x,y) memset(x,y,sizeof(x))
#define MCPY(a,b) memcpy(a,b,sizeof(b))
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,b,a) for(int i=b;i>=a;i--)
#define fi first
#define mp make_pair
#define se second
using namespace std;
#define int long long

inline int quickpow(int m,int n,int p){int b=1;while(n){if(n&1)b=b*m%p;n=n>>1;m=m*m%p;}return b;}
inline int getinv(int x,int p){return quickpow(x,p-2,p);}
inline int read(void){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){f=ch=='-'?-1:1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x * f;
}
const int MAXN = 1e5 + 100;
int n,len,a[MAXN],col[MAXN],pre[MAXN];
const int inf = 0x3F3F3F3F;
inline int isok(int x){
    //printf("%lld\n",x);
    rep(i,1,n) col[i] = (x > a[i]);
    //rep(i,1,n) printf("%lld ",col[i]);
    //puts("");
    //system("pause");
    rep(i,1,n) pre[i] = pre[i-1] + col[i];
    rep(i,len,n) if ((len)/2 == (pre[i] - pre[i-len])) return 1;
    return 0;
}
///------------------head------------------
signed main(signed argc, char *argv[]){
    n = read(),len = read();
    int L = inf,R = -inf;
    rep(i,1,n)  a[i] = read(),L = min(L,a[i]),R = max(R,a[i]);
    while(R - L > 100) {
        int mid = (L + R) >> 1;
        if (isok(mid)) L = mid + 1;
        else R = mid;
    }
    per(i,R,L) if (isok(i)) return printf("%lld\n",i),0;
    return 0;
}

/* Examples: */
/*

*/

/*

*/