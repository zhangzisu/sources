#include<bits/stdc++.h>
using namespace std;
const int N=100010,M=10000;
inline int read(){
    char ch=getchar(); int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch=getchar();}
    return x*f;
}
inline int lcm(int a,int b){return a/__gcd(a,b)*b;}
int p,s[N<<2],w[N<<2],a[N],len[N<<2],cir[N<<2][62];
bool inc[M],in[N<<2]; int nx[M],lz[N<<2];
void init(int x,int v){
    s[x]=v; in[x]=inc[v];
    if(in[x]){
        len[x]=1,cir[x][w[x]=0]=v;
        for(int u=nx[v];u!=v;u=nx[u]) cir[x][len[x]++]=u;
    }
}
void upd(int x){
    int lc=x<<1,rc=lc|1;
    s[x]=s[lc]+s[rc],in[x]=in[lc]&in[rc];
    if(in[x]){
        len[x]=lcm(len[lc],len[rc]);
        int tx=w[lc],ty=w[rc];
        for(int i=0;i<len[x];++i){
            cir[x][i]=cir[lc][tx++]+cir[rc][ty++];
            if(tx==len[lc])tx=0; if(ty==len[rc])ty=0;
        }
        w[x]=0;
    }
}
void bulid(int x,int l,int r){
    if(l==r){
        init(x,a[l]); return;
    }
    int lc=x<<1,rc=lc|1,mid=(l+r)>>1;
    bulid(lc,l,mid),bulid(rc,mid+1,r);
    upd(x);
}
void pushdown(int x){
    int c=lz[x],lc=x<<1,rc=lc|1; lz[x]=0;
    lz[lc]+=c,lz[rc]+=c; w[lc]+=c,w[rc]+=c;
    if(w[lc]>=len[lc])w[lc]%=len[lc]; s[lc]=cir[lc][w[lc]];
    if(w[rc]>=len[rc])w[rc]%=len[rc]; s[rc]=cir[rc][w[rc]];
}
void change(int x,int l,int r,int ql,int qr){
    if(l==ql&&r==qr&&in[x]){
        ++lz[x],++w[x]; if(w[x]==len[x])w[x]=0;
        s[x]=cir[x][w[x]]; return;
    }
    if(l==r){init(x,nx[s[x]]); return;}
    if(lz[x])pushdown(x); int mid=(l+r)>>1,lc=x<<1,rc=lc|1;
    if(qr<=mid)change(lc,l,mid,ql,qr);
    else if(ql>mid)change(rc,mid+1,r,ql,qr);
    else change(lc,l,mid,ql,mid),change(rc,mid+1,r,mid+1,qr);
    upd(x);
}
int query(int x,int l,int r,int ql,int qr){
    if(l==ql&&r==qr)return s[x];
    if(lz[x])pushdown(x); int mid=(l+r)>>1,lc=x<<1,rc=lc|1;
    if(qr<=mid)return query(lc,l,mid,ql,qr);
    else if(ql>mid)return query(rc,mid+1,r,ql,qr);
    return query(lc,l,mid,ql,mid)+query(rc,mid+1,r,mid+1,qr);
}
bool v[M];
int main()
{
    int n=read(),m=read(),i; p=read();
    for(i=1;i<=n;++i)a[i]=read();
    for(i=0;i<p;++i)nx[i]=(i*i)%p,inc[i]=1;
    for(i=0;i<p;++i) if(!v[i]){
        int y=i; while(!v[y])v[y]=1,y=nx[y];
        for(int t=i;t!=y;t=nx[t])inc[t]=0;
    }
    bulid(1,1,n);
    while(m--){
        int u=read(),l=read(),r=read();
        if(!u) change(1,1,n,l,r);
        else printf("%d\n",query(1,1,n,l,r));
    }
    return 0;
}