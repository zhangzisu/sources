#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define LL long long
#define N 100010
int n,x;
LL ans=0,res=0;
int fir[N],to[2*N],val[2*N],next[2*N],tot=0;
void adde(int u,int v,int w){
  next[tot]=fir[v],to[tot]=u,val[tot]=w,fir[v]=tot++;
  next[tot]=fir[u],to[tot]=v,val[tot]=w,fir[u]=tot++;
}
void dfs(int x,int fa,LL deep){
  res=std::res(res,deep);
  for (int i=fir[x];~i;i=next[i]){
    if (to[i]!=fa)dfs(to[i],x,deep + val[i]);
  }
}
int main(){
  scanf("%d%d",&n,&x);
  memset(fir,-1,sizeof(fir));
  for (int i=1;i < n;i++){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    adde(u,v,w);
    ans+=w;
  }
  dfs(x,0,0);
  printf("%lld\n",2*ans-res);
}