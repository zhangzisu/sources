#include<algorithm>
#include"gap.h"
typedef long long lnt;const lnt INF=1e18;lnt cao(int n){lnt min,max,ans=0;MinMax(0,INF,&min,&max);
if(n==2)return max-min;for(int i=1;i<(n+1)/2;i++){lnt tmin,tmax;MinMax(min+1,max-1,&tmin,&tmax);
if(!~tmin||!~tmax)break;ans=std::max(ans,tmin-min);ans=std::max(ans,max-tmax);min=tmin;max=tmax;
if(max-min<=1)break;}return ans=std::max(ans,max-min);}lnt gao(int n){lnt min,max,ans=0;
MinMax(0,INF,&min,&max);if(n==2)return max-min;lnt len=max-min-1;lnt gap=(len+n-3)/(n-2);
lnt l=min+1,r;for(int i=2;l<max&&i<n;i++){r=std::min(l+gap-1,max-1);lnt tmin,tmax;
MinMax(l,r,&tmin,&tmax);if(~tmin&&~tmax){ans=std::max(ans,tmin-min);min=tmax;}l=r+1;}
return ans=std::max(ans,max-min);}lnt findGap(int T,int N){return T==1?cao(N):gao(N);}