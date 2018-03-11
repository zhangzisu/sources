#include<bits/stdc++.h>

using namespace std;

#define N 600

int n,m,p,ans,f[1<<8][N];
char s1[N],s2[N],s[10][N];

int calc(int x){
	int ret=0;
	for (int i=0;i<n;i++)
		if (1<<i&x) ret+=strlen(s[i]+1);
	return ret;
}

int main(){
	scanf("%s%s%d",s1+1,s2+1,&n);
	m=strlen(s1+1); p=strlen(s2+1);
	for (int i=0;i<n;i++)
		scanf("%s",s[i]+1);
	memset(f,0x3f,sizeof f); f[0][0]=0;
	for (int i=0;i<1<<n;i++)
		for (int j=0;j<p;j++){
			if (f[i][j]>m) continue;
			for (int k=f[i][j]+1;k<=m;k++)
				if (s1[k]==s2[j+1]){
					f[i][j+1]=min(f[i][j+1],k); break;
				}
			if (f[i][j]==m) continue;
			for (int k=0;k<n;k++)
				if (!(1<<k&i)){
					int len=strlen(s[k]+1);
					for (int l=1;l<=len;l++){
						if (s[k][l]!=s2[j+l]) break;
						f[1<<k|i][j+l]=min(f[1<<k|i][j+l],f[i][j]);
					}
				}
		}
	ans=0x3f3f3f3f;
	for (int i=0;i<1<<n;i++)
		if (f[i][p]<=m) ans=min(ans,m+calc(i)-p);
	printf("%d\n",ans);
	
	return 0;
}
