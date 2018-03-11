#include <bits/stdc++.h>
#define X 5010
#define O 1000000007
#define L long long
using namespace std;
int e[X],o[X<<1],K[X<<1],t=0;inline void $(int u,int v){
K[t]=e[u],o[t]=v,e[u]=t++;K[t]=e[v],o[t]=u,e[v]=t++;}int n,z[X],q[X],r,s;void G(int x,int fa){z[x]=1;
for(int i=e[x];~i;i=K[i]){if(o[i]==fa)continue;G(o[i],x);z[x]+=z[o[i]];q[x]=max(q[x],z[o[i]]);}q[x]=max(q[x],n-z[x]);
if(q[x] < q[r])r=x,s=1;else if(q[x]==q[r])s=2;}L F[X],V[X],f[2][X];inline L fpow(L x,int p){L r=1;while(p){
if(p & 1)(r*=x)%=O;(x*=x)%=O;p>>=1;}return r;}inline L C(int n,int m){return F[n]*V[m]%O*V[n-m]%O;}int main(){F[0]=1;
for(int i=1;i < X;i++)F[i]=F[i-1]*i%O;V[X-1]=fpow(F[X-1],O-2);for(int i=X-1;i;i--)V[i-1]=V[i]*i%O;cin>> n;memset(e,-1,sizeof(e));for(int i=1;i < n;i++){
int u,v;cin>>u>>v;$(u,v);}q[r=0]=n+ 1;G(1,0);if(s>1){cout<<F[z[1]>> 1]*F[z[1]>> 1]%O<<endl;return 0;}G(r,0);
int now=0,pre=1;f[pre][0]=1;for(int i=e[r];~i;i=K[i]){memset(f[now],0,sizeof(f[now]));for(int j=0;j <=n;j++){
for(int k=0;k <=z[o[i]];k++)(f[now][j+ k]+=f[pre][j]*C(z[o[i]],k)%O*C(z[o[i]],k)% O*F[k]%O)%=O;}swap(pre,now);}L ans=0;
for(int i=0;i <=n;i++)(ans -=f[pre][i]*(i & 1 ? 1 : -1)*F[n-i])%=O;cout<<((ans+=O)%=O)<<endl;return 0;}