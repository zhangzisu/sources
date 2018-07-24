#include<cstdio>
#include<algorithm>
int t,n,m,stk[41],a[41],ok;
int dfs(int len1,int len2){if(ok==1)return 1;if(len1+len2 >= n)return ok=1;
if(len1<len2)std::swap(len1,len2);int now=a[len1+len2+1];if(len1==len2){
stk[len1+1]=now;if(len1<m&&dfs(len1+1,len2))return 1;return 0;}
stk[len1+1]=now;if(len1<m&&dfs(len1+1,len2))return 1;
if(now!=stk[len2+1])return 0;return dfs(len1,len2+1);}
int main(){for(scanf("%d",&t);t;t--){scanf("%d",&n);
m=n>>1;for(int i=1;i <= n;i++)scanf("%d",&a[i]);
ok=false;if(dfs(0,0))puts("Frederica Bernkastel");else
puts("Furude Rika");}return 0;}