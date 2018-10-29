#include<stdio.h>
#define Q 10000
#define next(x) (((x)+1)%Q)
short n,i,j,x,y;int r,h,t,q[Q];unsigned p[31250];
int g(int d){return(p[d>>5]>>(d&31))&1;}
void s(int d){p[d>>5]|=(1<<(d&31));}
int _(short x,short y){return(int)x*n+y;}
int main(){scanf("%hd",&n);for(i=0;i<n;i++){
for(j=0;j<n;j++){scanf("%d",&r);if(r)s(_(i,j));
}}r=0;for(i=0;i<n;i++){for(j=0;j<n;j++){
if(g(_(i,j)))continue;r++;s(q[h=t=0]=_(i,j));
while(h!=next(t)){x=q[h]/n;y=q[h]%n;h=next(h);
if(x>0&&!g(_(x-1,y)))s(q[t=next(t)]=_(x-1,y));
if(x<n-1&&!g(_(x+1,y)))s(q[t=next(t)]=_(x+1,y));
if(y>0&&!g(_(x,y-1)))s(q[t=next(t)]=_(x,y-1));
if(y<n-1&&!g(_(x,y+1)))s(q[t=next(t)]=_(x,y+1));
}}}printf("%d\n",r);return 0;}