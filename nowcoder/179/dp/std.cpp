#include<bits/stdc++.h>

using namespace std;

#define N 120

int n,m,x,y,z;
bool f[N][N][N],g[N],h[N];

int main(){
	scanf("%d%d",&n,&m);
	while (m--){
		scanf("%d%d",&x,&y);
		f[0][x][y]=1;
	}
	for (int t=1;t<=30;++t)
		for (int k=1;k<=n;++k)
			for (int i=1;i<=n;++i)
				for (int j=1;j<=n;++j)
					f[t][i][j]|=f[t-1][i][k]&f[t-1][k][j];
	scanf("%d",&m);
	while (m--){
		scanf("%d%d%d",&z,&x,&y);
		memset(g,0,sizeof g); g[x]=1;
		for (int t=0;t<=30;++t)
			if (z>>t&1){
				memset(h,0,sizeof h);
				for (int k=1;k<=n;++k)
					for (int j=1;j<=n;++j)
						h[j]|=g[k]&f[t][k][j];
				memcpy(g,h,sizeof g);
			}
		puts(g[y]?"YES":"NO");
	}
	
	return 0;
}