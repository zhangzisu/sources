#include<bits/stdc++.h>
typedef double d;d E=1e-7;int n,m,i;d v[1<<20],ans;void FMT(d*f,d d){for(i=0;i<n;i++){
for(int j=0;j<m;j++){if(j&(1<<i))continue;f[j|(1<<i)]+=d*f[j];}}}
int main(){scanf("%d",&n);m=1<<n;for(i=0;i<m;i++)scanf("%lf",&v[i]);
FMT(v,1);for(i=0;i<m;i++)v[i]=(abs(1-v[i])<=E?0:-1/(1-v[i]));
FMT(v,-1);if(v[m-1]<=E)puts("INF");else printf("%f\n",v[m-1]);return 0;}